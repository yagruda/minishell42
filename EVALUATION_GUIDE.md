# Minishell - Evaluation Guide

## Quick Overview

This is a simplified shell implementation (like bash) written in C. It reads commands from the user, processes them, and executes them just like a real shell.

---

## How It Works - Simple Explanation

### The Big Picture

When you type a command like `echo hello | grep h > output.txt`, the shell needs to:

1. **Understand** what you typed (Tokenization)
2. **Organize** the pieces (Parsing)
3. **Process** special things like `$HOME` (Expansion)
4. **Run** the commands (Execution)

Think of it like a factory assembly line - each stage does one specific job and passes the result to the next stage.

---

## The Four Stages

### Stage 1: Tokenization (Breaking It Down)

**What it does**: Breaks your input into pieces (tokens).

**Example**:
```
Input:  echo hello | cat
Tokens: [echo] [hello] [|] [cat]
```

**How to explain it**:
> "First, the tokenizer reads the input string character by character and breaks it into tokens. It recognizes special operators like pipes and redirections, and handles quotes properly. For example, it knows that 'hello world' with quotes should be ONE token, not two."

**Key points**:
- Handles quotes (single and double)
- Recognizes operators: `|`, `<`, `>`, `>>`, `<<`
- Preserves spaces inside quotes
- Each token has a type (WORD, PIPE, REDIRECT_IN, etc.)

**Code location**: `src/tokenizer/tokenizer_core_i.c`

---

### Stage 2: Parsing (Organizing)

**What it does**: Organizes tokens into command structures.

**Example**:
```
Tokens: [echo] [hello] [>] [file.txt] [|] [cat]

Result:
  Command 1:
    - argv: ["echo", "hello"]
    - redirections: [OUT: file.txt]
  Command 2:
    - argv: ["cat"]
    - redirections: []
```

**How to explain it**:
> "The parser takes the flat list of tokens and builds a tree-like structure of commands. It groups words into command arguments and attaches redirections to the right commands. Pipes separate different commands that will be connected together."

**Key points**:
- Creates linked list of commands
- Each command has an array of arguments (argv)
- Each command has a list of redirections
- Pipes create separate commands

**Code location**: `src/parser/parser_core_i.c`

---

### Stage 3: Expansion (Processing Variables)

**What it does**: Expands `$VAR` to their values and removes quotes.

**Example**:
```
Before: ["echo"] ["$HOME"] ['$USER']
After:  ["echo"] ["/Users/admin"] ["$USER"]
```

**How to explain it**:
> "The expander goes through each argument and looks for dollar signs. When it finds `$VAR`, it looks up that variable in the environment and replaces it with its value. It also handles special variables like `$?` for the last exit code. Single quotes prevent expansion, double quotes allow it. After expansion, all quote characters are removed."

**Key points**:
- `$VAR` becomes the value of environment variable VAR
- `$?` becomes the exit code of the last command
- Single quotes `'...'` prevent expansion
- Double quotes `"..."` allow expansion
- Quotes are removed after expansion

**Code location**: `src/expander/expander_i.c`

---

### Stage 4: Execution (Running)

**What it does**: Actually runs the commands.

**How to explain it**:
> "The executor checks if it's a built-in command or an external program. For built-ins without redirections, we run them directly in the parent process. For external commands or pipelines, we use `fork()` to create child processes. We set up pipes to connect commands in a pipeline and configure file descriptors for redirections. Finally, we use `execve()` to replace the child process with the actual command."

**Key concepts to understand**:

#### Built-in vs External Commands

**Built-ins** (run in parent):
- `cd`, `export`, `exit`, `unset` - MUST run in parent to modify shell state
- `echo`, `pwd`, `env` - can run in parent for efficiency

**External** (run in child):
- Everything else (`ls`, `grep`, `cat`, etc.)
- Found using PATH environment variable

#### Single Command
```
1. Check if builtin without redirections → run in parent
2. Otherwise → fork()
3. Child: setup redirections, then exec command
4. Parent: wait for child and collect exit status
```

#### Pipeline (e.g., `ls | grep txt | wc -l`)
```
1. Create pipes for communication
2. Fork a child for EACH command
3. Connect commands with pipes:
   - Command 1: stdout → pipe → Command 2 stdin
   - Command 2: stdout → pipe → Command 3 stdin
4. Wait for all children to complete
```

**Code location**: `src/executor/executor.c`

---

## Common Evaluation Questions

### 1. "Why do you need built-in commands?"

**Answer**:
> "Some commands like `cd` and `export` need to modify the shell's own state. If we ran them in a child process (which is a copy), the changes would happen in the child and disappear when it exits. The parent shell wouldn't be affected. So these MUST run in the parent process."

### 2. "How do pipes work?"

**Answer**:
> "Pipes are a Unix mechanism for inter-process communication. We call `pipe()` which gives us two file descriptors - a read end and a write end. We then fork children for each command. The first command's stdout is redirected to the write end of the pipe, and the second command's stdin is redirected to the read end. Whatever the first command writes goes directly to the second command."

**Visual**:
```
[Process 1] --stdout--> [pipe write end]
                              ↓
                        [pipe read end] --stdin--> [Process 2]
```

### 3. "How do you handle quotes?"

**Answer**:
> "We handle quotes during tokenization and expansion. During tokenization, quotes tell us to treat spaces as part of the word instead of separators. During expansion, single quotes prevent variable expansion while double quotes allow it. After expansion, we remove the quote characters themselves."

Example:
```
echo '$HOME' "$HOME"
     ↓        ↓
     $HOME    /Users/admin
```

### 4. "What's the difference between `>` and `>>`?"

**Answer**:
> "`>` truncates the file (starts fresh), while `>>` appends to the file. We implement this using the `open()` system call with different flags: `O_TRUNC` for `>` and `O_APPEND` for `>>`."

### 5. "How do you handle memory?"

**Answer**:
> "We have clear ownership of memory. After each command execution, we call a cleanup function that frees all tokens, command structures, and redirections. We've tested with valgrind to ensure no leaks. All string operations use our libft functions which handle memory safely."

### 6. "How do you find commands to execute?"

**Answer**:
> "If the command contains a `/`, we use it as a direct path. Otherwise, we look up the PATH environment variable, split it by colons, and try appending the command name to each directory. We check each path with `access()` to see if it exists and is executable. The first match is used."

Example:
```
PATH=/usr/bin:/bin
Command: ls
Try: /usr/bin/ls → exists → use it!
```

### 7. "What are the main data structures?"

**Answer**:
> "We have three main structures:
>
> 1. **t_token**: Linked list of tokens from the input
> 2. **t_cmd**: Linked list of commands, each with argv array and redirection list
> 3. **t_shell**: Main state containing tokens, commands, environment, and exit code
>
> The flow is: input → tokens → commands → execution"

### 8. "How do you handle signals?"

**Answer**:
> "In interactive mode (waiting for input), Ctrl+C displays a new prompt but doesn't exit. Ctrl+D (EOF) exits gracefully. Ctrl+\\ is ignored. When a command is running, these signals go to the child process, and we handle the exit status appropriately (e.g., 130 for Ctrl+C)."

### 9. "How do heredocs work?"

**Answer**:
> "A heredoc (`<<`) reads input until it sees the delimiter. We read lines using `readline()` and typically use a temporary mechanism or pipe to store the content. When the command runs, we redirect stdin to read from that stored content."

---

## Demo Script for Evaluation

Here's a good sequence to demonstrate functionality:

```bash
# Start minishell
./minishell

# 1. Simple command
minishell> echo hello world

# 2. Built-in commands
minishell> pwd
minishell> cd ..
minishell> pwd
minishell> cd -

# 3. Environment variables
minishell> echo $HOME
minishell> echo $USER
minishell> export TEST=hello
minishell> echo $TEST
minishell> env | grep TEST

# 4. Exit status
minishell> ls
minishell> echo $?
minishell> ls nonexistent
minishell> echo $?

# 5. Redirections
minishell> echo "test content" > file.txt
minishell> cat file.txt
minishell> echo "more content" >> file.txt
minishell> cat file.txt

# 6. Input redirection
minishell> cat < file.txt

# 7. Pipes
minishell> ls -l | grep minishell
minishell> cat file.txt | wc -l
minishell> echo "one two three" | wc -w

# 8. Complex pipeline
minishell> ls -l | grep ".c" | wc -l

# 9. Quotes
minishell> echo "Hello    World"
minishell> echo 'Hello    World'
minishell> echo "$HOME"
minishell> echo '$HOME'

# 10. Multiple redirections
minishell> cat < file.txt > output.txt
minishell> cat output.txt

# 11. Exit
minishell> exit
```

---

## Key Implementation Details to Mention

### 1. Process Creation Flow
```
Parent Process (minishell)
    ↓ fork()
    ├─→ Parent: wait for child
    └─→ Child: setup redirections, then execve()
```

### 2. PATH Resolution
```
1. Check if command has '/' → use as absolute/relative path
2. Otherwise, get PATH from environment
3. Split PATH by ':'
4. For each directory, try: directory + '/' + command
5. Use access() to check if executable
6. Return first valid path
```

### 3. Redirection Setup
```
1. Open file with appropriate flags (O_RDONLY, O_WRONLY, etc.)
2. Use dup2() to redirect file descriptor
3. Close original file descriptor
4. Multiple redirections processed in order
```

### 4. Pipeline Setup (3 commands example)
```
1. Create 2 pipes (N-1 pipes for N commands)
2. Fork child 1:
   - Close read end of pipe 1
   - dup2(pipe1_write, stdout)
   - Close all other pipe fds
   - execve()
3. Fork child 2:
   - dup2(pipe1_read, stdin)
   - dup2(pipe2_write, stdout)
   - Close all other pipe fds
   - execve()
4. Fork child 3:
   - Close write end of pipe 2
   - dup2(pipe2_read, stdin)
   - Close all other pipe fds
   - execve()
5. Parent closes all pipes and waits for all children
```

---

## Error Handling

We handle these error cases:

1. **Syntax Errors**: Unclosed quotes, invalid pipes, invalid redirections
2. **Command Not Found**: Exit code 127
3. **Permission Denied**: Exit code 126
4. **File Not Found**: Appropriate error message
5. **Fork Failures**: Error message and graceful degradation
6. **Allocation Failures**: Check all malloc returns

---

## Testing Tips

### What to Test:

1. **Basic Commands**: `ls`, `pwd`, `echo`
2. **Built-ins**: All 7 built-in commands
3. **Pipes**: Single and multiple
4. **Redirections**: `<`, `>`, `>>`, `<<`
5. **Quotes**: Single, double, mixed
6. **Variables**: Regular and special (`$?`)
7. **Signals**: Ctrl+C, Ctrl+D, Ctrl+\\
8. **Edge Cases**: Empty input, syntax errors
9. **Memory**: Run with valgrind
10. **Comparison**: Compare output with bash

### Test Command:
```bash
# Compare with bash
bash -c "echo hello | cat"
./minishell -c "echo hello | cat"  # if you implement -c flag
```

---

## Common Pitfalls to Avoid During Evaluation

1. **Don't forget**: Built-ins without redirections run in parent
2. **Don't forget**: Close all pipe file descriptors in all processes
3. **Don't forget**: Wait for all child processes
4. **Don't forget**: Free all allocated memory
5. **Don't forget**: Handle signals properly
6. **Don't forget**: Set proper exit codes

---

## Summary Statement for Evaluation

> "Minishell is a shell implementation that processes commands in four stages: tokenization, parsing, expansion, and execution. The tokenizer breaks input into tokens while handling quotes and operators. The parser organizes tokens into command structures with arguments and redirections. The expander processes variables and removes quotes. Finally, the executor runs commands either in the parent process for built-ins or in child processes for external commands, using pipes to connect commands in pipelines and dup2 for redirections. The implementation properly handles memory, signals, and exit codes."

---

## Useful Resources to Review Before Evaluation

1. **System Calls**: `fork`, `execve`, `pipe`, `dup2`, `wait`, `open`, `close`
2. **Functions**: `readline`, `add_history`
3. **Concepts**: Process creation, file descriptors, pipes, signals
4. **Bash Manual**: For behavior reference

---

## Quick Reference: File Descriptors

```
0 = stdin  (standard input)
1 = stdout (standard output)
2 = stderr (standard error)
```

**Redirection examples**:
- `cmd > file`: stdout (fd 1) → file
- `cmd < file`: stdin (fd 0) ← file
- `cmd 2> file`: stderr (fd 2) → file
- `cmd1 | cmd2`: cmd1 stdout → pipe → cmd2 stdin

---

Good luck with your evaluation!
