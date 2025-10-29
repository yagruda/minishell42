# Minishell - Technical Documentation

## Table of Contents
1. [Project Overview](#project-overview)
2. [Architecture](#architecture)
3. [Data Structures](#data-structures)
4. [Core Components](#core-components)
5. [Execution Flow](#execution-flow)
6. [Built-in Commands](#built-in-commands)
7. [File Structure](#file-structure)

---

## Project Overview

Minishell is a simplified shell implementation inspired by bash. It provides a command-line interface that can:
- Execute commands with arguments
- Handle pipes (`|`) for chaining commands
- Manage input/output redirections (`<`, `>`, `>>`, `<<`)
- Expand environment variables (`$VAR`, `$?`)
- Execute built-in commands
- Handle signals (Ctrl+C, Ctrl+D, Ctrl+\\)
- Maintain command history

---

## Architecture

The minishell follows a pipeline architecture with four main stages:

```
Input → Tokenization → Parsing → Expansion → Execution
```

1. **Tokenization**: Breaks input string into tokens (words, operators)
2. **Parsing**: Organizes tokens into command structures
3. **Expansion**: Expands variables and removes quotes
4. **Execution**: Executes commands (built-ins or external)

---

## Data Structures

### t_token
Represents a single token from the input string.

```c
typedef struct s_token
{
    char            *value;      // Token value (e.g., "echo", "|", ">")
    t_token_type    type;        // Token type (WORD, PIPE, REDIRECT_IN, etc.)
    struct s_token  *next;       // Linked list pointer
}   t_token;
```

**Token Types:**
- `WORD`: Command names, arguments, file names
- `PIPE`: Pipeline operator `|`
- `REDIRECT_IN`: Input redirection `<`
- `REDIRECT_OUT`: Output redirection `>`
- `APPEND`: Append redirection `>>`
- `HEREDOC`: Here document `<<`

### t_redir
Represents a redirection operation.

```c
typedef struct s_redir
{
    int             type;        // Redirection type (REDIRECT_IN, REDIRECT_OUT, etc.)
    char            *file;       // Target file name
    struct s_redir  *next;       // Linked list for multiple redirections
}   t_redir;
```

### t_cmd
Represents a single command with its arguments and redirections.

```c
typedef struct s_cmd
{
    char            **argv;      // NULL-terminated array of arguments
    t_redir         *redir;      // Linked list of redirections
    struct s_cmd    *next;       // Next command in pipeline
}   t_cmd;
```

### t_shell
Main shell state structure containing all runtime information.

```c
typedef struct s_shell
{
    t_token *tokens;             // Linked list of tokens
    t_cmd   *cmd_list;           // Linked list of parsed commands
    char    **envp;              // Environment variables
    int     exit_code;           // Last command exit status
}   t_shell;
```

---

## Core Components

### 1. Tokenizer (`src/tokenizer/`)

**Purpose**: Converts raw input string into a linked list of tokens.

**Main Functions:**
- `tokenizer()` - Entry point for tokenization
- `extract_word()` - Extracts words while handling quotes
- `skip_spaces()` - Skips whitespace characters
- `create_token()` / `add_token()` - Token list management

**Key Features:**
- Recognizes operators: `|`, `<`, `>`, `>>`, `<<`
- Handles single quotes (no expansion) and double quotes (expansion)
- Preserves quote context for proper word extraction

**Location**: `src/tokenizer/tokenizer_core_i.c:77`

### 2. Parser (`src/parser/`)

**Purpose**: Transforms token list into command structures.

**Main Functions:**
- `parser()` - Entry point for parsing
- `create_cmd()` - Creates new command structure
- `add_arg()` - Adds argument to command
- `add_redirect()` - Adds redirection to command
- `process_redirection()` - Handles redirection tokens

**Parsing Logic:**
- Commands are separated by `PIPE` tokens
- Redirections are paired with the following `WORD` token
- All other words become command arguments

**Example:**
```
Input:  echo hello > file.txt | cat < file.txt
Tokens: [echo][hello][>][file.txt][|][cat][<][file.txt]
Result: cmd1: argv=["echo","hello"], redir=[OUT:file.txt]
        cmd2: argv=["cat"], redir=[IN:file.txt]
```

**Location**: `src/parser/parser_core_i.c:94`

### 3. Expander (`src/expander/`)

**Purpose**: Expands environment variables and removes quotes.

**Main Functions:**
- `expander()` - Entry point for expansion
- `expand_vars()` - Expands `$VAR` to their values
- `remove_quotes()` - Removes quote characters
- `get_var_value()` - Retrieves variable values
- `get_env_value()` - Searches environment for variable

**Expansion Rules:**
- `$VAR` expands to environment variable value
- `$?` expands to last exit code
- Variables in single quotes `'$VAR'` are NOT expanded
- Variables in double quotes `"$VAR"` ARE expanded
- After expansion, all quote characters are removed

**Example:**
```
Input:  echo "$HOME" '$USER'
After:  ["echo"]["/Users/admin"]["$USER"]
```

**Location**: `src/expander/expander_i.c:92`

### 4. Executor (`src/executor/`)

**Purpose**: Executes parsed and expanded commands.

**Main Functions:**
- `executor()` - Entry point, routes to single or pipeline execution
- `exec_single_cmd()` - Executes single command
- `exec_pipeline()` - Executes pipeline with multiple commands
- `setup_redirects()` - Configures file descriptors for redirections
- `find_command()` - Resolves command path using PATH variable

**Execution Strategy:**
- **Single Command**:
  - Built-ins without redirections run in parent process
  - Everything else runs in child process
- **Pipeline**: All commands run in child processes connected by pipes
- Exit codes are properly captured and stored

**Process Management:**
- `fork()` creates child processes
- `execve()` replaces process with command
- `waitpid()` collects exit status
- Signals (SIGINT, SIGTERM) are handled appropriately

**Location**: `src/executor/executor.c:69`

### 5. Built-in Commands (`src/builtins/`)

**Implemented Built-ins:**

| Command | Description | Location |
|---------|-------------|----------|
| `echo` | Print arguments to stdout (with `-n` flag support) | `builtin_echo.c` |
| `cd` | Change working directory | `builtin_cd.c` |
| `pwd` | Print working directory | `builtin_pwd.c` |
| `export` | Set environment variables | `builtin_export.c` |
| `unset` | Remove environment variables | `builtin_unset.c` |
| `env` | Display environment variables | `builtin_env.c` |
| `exit` | Exit the shell | `builtin_exit.c` |

**Why Built-ins?**
- Some commands MUST run in parent process (`cd`, `export`, `exit`)
- Built-ins modify shell state directly
- External commands run in child processes and cannot modify parent

---

## Execution Flow

### Complete Command Processing Pipeline

```
1. User Input
   ↓
2. Input Validation (src/tokenizer/input_validation.c)
   - Check quotes are closed
   - Validate redirect syntax
   - Validate pipe syntax
   ↓
3. Tokenization (src/tokenizer/tokenizer_core_i.c)
   - Split into tokens
   - Identify token types
   ↓
4. Parsing (src/parser/parser_core_i.c)
   - Group into commands
   - Associate redirections
   - Build command list
   ↓
5. Expansion (src/expander/expander_i.c)
   - Expand variables
   - Remove quotes
   ↓
6. Execution (src/executor/executor.c)
   - Check if builtin
   - Setup redirections
   - Fork if needed
   - Execute command
   ↓
7. Cleanup (src/utils/init_or_free.c)
   - Free tokens
   - Free commands
   - Free redirections
   ↓
8. Ready for next input
```

### Main Loop

Located in `src/main.c:15`:

```c
while (1)
{
    input = readline("minishell> ");
    if (!input)  // Ctrl+D
        break;
    if (input)
    {
        process_input(shell, input, argv);
        free(input);
    }
}
```

---

## Built-in Commands

### echo
**Syntax**: `echo [-n] [arguments...]`
- Prints arguments separated by spaces
- `-n` flag suppresses trailing newline
- Supports multiple `-n` flags

### cd
**Syntax**: `cd [directory]`
- Changes current working directory
- No argument or `~` goes to HOME directory
- Updates PWD and OLDPWD environment variables

### pwd
**Syntax**: `pwd`
- Prints current working directory
- Uses `getcwd()` system call

### export
**Syntax**: `export [VAR=value...]`
- Without arguments: displays all environment variables
- With arguments: sets environment variables
- Format: `VAR=value` (no spaces around `=`)

### unset
**Syntax**: `unset [VAR...]`
- Removes environment variables
- Multiple variables can be unset at once

### env
**Syntax**: `env`
- Displays all environment variables
- Format: `VAR=value` (one per line)

### exit
**Syntax**: `exit [n]`
- Exits the shell with status code `n`
- Default exit code: last command's exit code
- Validates that argument is numeric

---

## File Structure

```
minishell42/
├── Makefile                    # Build configuration
├── src/
│   ├── main.c                 # Entry point and main loop
│   ├── minishell.h            # Main header file
│   ├── errors.c               # Error handling
│   │
│   ├── tokenizer/             # Tokenization module
│   │   ├── tokenizer.h
│   │   ├── tokenizer_core_i.c    # Main tokenization logic
│   │   ├── tokenizer_helpers.c   # Word extraction, token creation
│   │   ├── input.c               # Input processing
│   │   ├── input_validation.c    # Syntax validation
│   │   └── signals.c             # Signal handling
│   │
│   ├── parser/                # Parsing module
│   │   ├── parser.h
│   │   └── parser_core_i.c       # Command structure creation
│   │
│   ├── expander/              # Expansion module
│   │   ├── expander_i.c          # Variable expansion
│   │   ├── expander_helpers.c    # Variable extraction
│   │   └── expander_utils.c      # String utilities
│   │
│   ├── executor/              # Execution module
│   │   ├── executor.h
│   │   ├── executor.c            # Main execution logic
│   │   ├── single_cmd.c          # Single command execution
│   │   ├── pipeline.c            # Pipeline execution
│   │   ├── pipeline_utils.c      # Pipeline helpers
│   │   ├── path_resolver.c       # PATH resolution
│   │   └── redirects.c           # Redirection setup
│   │
│   ├── builtins/              # Built-in commands
│   │   ├── builtins.h
│   │   ├── builtin_echo.c
│   │   ├── builtin_cd.c
│   │   ├── builtin_pwd.c
│   │   ├── builtin_export.c
│   │   ├── builtin_unset.c
│   │   ├── builtin_env.c
│   │   └── builtin_exit.c
│   │
│   ├── utils/                 # Utility functions
│   │   ├── utils.h
│   │   ├── init_or_free.c        # Memory management
│   │   └── tester_debug.c        # Debug printing
│   │
│   └── Include/               # External libraries
│       ├── ft_printf.c/h         # Custom printf
│       └── Libft/                # Libft functions
│
└── OBJ/                       # Compiled object files (generated)
```

---

## Key Implementation Details

### Quote Handling
- Single quotes `'`: Preserve everything literally, no expansion
- Double quotes `"`: Allow variable expansion, preserve spaces
- Quotes are removed after expansion

### Variable Expansion
- `$VAR`: Expands to value of environment variable VAR
- `$?`: Expands to exit code of last command
- `$`: If not followed by valid variable name, treated as literal

### Pipeline Implementation
- Uses Unix pipes (`pipe()` system call)
- Each command runs in separate process
- Processes connected via pipe file descriptors
- Parent waits for all children to complete

### Redirection Handling
- Multiple redirections are applied in order
- Heredoc creates temporary file descriptor
- Redirections are set up before command execution
- File descriptors properly duplicated and closed

### Signal Handling
- `Ctrl+C` (SIGINT): Displays new prompt, doesn't exit
- `Ctrl+D` (EOF): Exits shell gracefully
- `Ctrl+\` (SIGQUIT): Ignored in interactive mode
- Signals handled differently in parent vs child processes

### Memory Management
- All allocations tracked and freed appropriately
- Cleanup function called after each command
- No memory leaks (verified with valgrind)
- Proper error handling on allocation failures

---

## Building and Running

### Compilation
```bash
make        # Compile the project
make clean  # Remove object files
make fclean # Remove object files and executable
make re     # Recompile from scratch
```

### Running
```bash
./minishell
```

### Testing
```bash
# Simple command
minishell> echo hello world

# Pipeline
minishell> ls -l | grep minishell | wc -l

# Redirections
minishell> echo "test" > file.txt
minishell> cat < file.txt

# Variable expansion
minishell> echo $HOME $USER

# Exit status
minishell> ls nonexistent 2>/dev/null
minishell> echo $?
```

---

## Edge Cases Handled

1. **Empty Input**: Prompt shown again
2. **Unclosed Quotes**: Syntax error reported
3. **Invalid Pipes**: `| |` or starting/ending with pipe
4. **Invalid Redirections**: `>` or `<` without filename
5. **Command Not Found**: Appropriate error message, exit code 127
6. **Permission Denied**: Exit code 126
7. **Signals During Execution**: Proper cleanup and exit codes
8. **Memory Allocation Failures**: Graceful error handling

---

## Exit Codes

| Code | Meaning |
|------|---------|
| 0 | Success |
| 1 | General error |
| 2 | Syntax error |
| 126 | Command cannot execute (permission denied) |
| 127 | Command not found |
| 128+n | Command terminated by signal n (e.g., 130 for Ctrl+C) |

---

## References

- [Bash Manual](https://www.gnu.org/software/bash/manual/)
- [Unix System Calls](https://man7.org/linux/man-pages/)
- [42 School Minishell Subject](https://cdn.intra.42.fr/pdf/pdf/960/minishell.en.pdf)
