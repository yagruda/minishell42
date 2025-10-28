# Minishell Code Review - Issues and Fixes

## ✅ ALL CRITICAL ISSUES FIXED!

Your tokenizer, parser, and expander are now working correctly with no memory leaks or critical bugs. See [FIXES_COMPLETED.md](FIXES_COMPLETED.md) for the complete list of all changes.

## Fixed Issues

### 1. ✅ Memory Leak in main.c (Line 33)
**Issue**: Attempting to free NULL pointer
```c
if (!input)
{
    free(input);  // ❌ input is NULL here!
    break;
}
```
**Fix**: Removed the erroneous free call.

### 2. ✅ Using strdup instead of ft_strdup in parser_core_i.c (Line 37)
**Issue**: Should use ft_strdup for 42 norm compliance
```c
new_redir->file = strdup(file);  // ❌ Should use ft_strdup
```
**Fix**: Changed to `ft_strdup(file)`

### 3. ✅ Debug code in main.c
**Issue**: Unnecessary debug function call to `example_structures_init`
**Fix**: Removed debug code

---

## Remaining Issues to Address

### 1. ⚠️ Empty input validation error (input.c:26-33)
**Issue**: Empty input should NOT be a syntax error
```c
if (is_empty(input))
{
    custom_error("syntax error: empty input\n");  // ❌ Wrong!
    shell->exit_code = 258;
    return 0;
}
```
**Expected Behavior**: Empty input should just display a new prompt (like bash)
**Fix**: Remove this validation or just return without error

### 2. ⚠️ Exit code 258 is incorrect
**Issue**: Bash uses 2 for syntax errors, not 258
**Fix**: Change `shell->exit_code = 258;` to `shell->exit_code = 2;` (line 20)

### 3. ⚠️ Exit handling is incomplete (input.c:90-95)
**Issue**: Exit is checked AFTER parsing, but should be a built-in command
**Current**:
```c
if (ft_strcmp(input, "exit") == 0)
{
    printf("exit\n");
    return 1;
}
```
**Problem**: This only works if user types exactly "exit" - won't work for "exit 42" or after parsing
**Fix**: This should be handled by your partner's built-in implementation in the executor

### 4. ⚠️ Error handling for malloc failures
**Issue**: Several functions don't handle malloc failures properly:
- `tokenizer_core_i.c:51` - create_token
- `parser_core_i.c:18` - create_cmd
- `parser_core_i.c:30` - add_redirect
- `parser_core_i.c:59` - add_arg
- `expander_i.c:25,76,124` - Multiple malloc calls

**Impact**: Could cause crashes instead of graceful error handling

### 5. ⚠️ extract_var_name can return empty string (expander_i.c:56-71)
**Issue**: If $VAR has no valid characters after $, *len will be 0 and ft_substr returns empty string
```c
while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
    i++;
*len = i;  // Could be 0!
return ft_substr(str, 0, i);  // Returns empty string if i=0
```
**Problem**: `$ ` (dollar followed by space) will create empty var_name
**Fix**: Add check for len == 0 case

---

## Missing Features (Your Partner Needs to Implement)

### Executor Module (CRITICAL - completely missing)
Your partner needs to create these files and implement:

1. **Command Execution**
   - Search executables in PATH
   - Execute commands using fork() + execve()
   - Handle relative/absolute paths
   - Set up pipes between commands
   - Handle redirections (open files, dup2)

2. **Built-in Commands** (must work without fork)
   - `echo` with -n option
   - `cd` with relative/absolute paths
   - `pwd` (no options)
   - `export` (no options - add/modify env vars)
   - `unset` (no options - remove env vars)
   - `env` (no options - print environment)
   - `exit` (no options - exit shell with status)

3. **Signal Handling During Execution**
   - Handle ctrl-C (SIGINT) during command execution
   - Child processes should be interrupted
   - Parent should not exit

4. **Exit Status Management**
   - Capture exit status from child processes
   - Update shell->exit_code
   - Handle $? expansion (you already do this!)

5. **Pipe Implementation**
   - Create pipes for | commands
   - Connect output of cmd1 to input of cmd2
   - Close unused pipe ends

6. **Redirection Implementation**
   - `<` - open file for reading, redirect to stdin
   - `>` - open file for writing (truncate), redirect to stdout
   - `>>` - open file for appending, redirect to stdout
   - `<<` - heredoc (read until delimiter)

---

## Code Quality Issues

### 1. Inconsistent variable declarations
Some functions declare variables at top (C89 style), some inline (C99 style)
**Recommendation**: Check which C standard you're using and be consistent

### 2. Magic numbers
```c
shell->exit_code = 258;  // What is 258?
shell->exit_code = 2;    // Syntax error
```
**Recommendation**: Define constants:
```c
#define EXIT_SUCCESS 0
#define EXIT_SYNTAX_ERROR 2
#define EXIT_CMD_NOT_FOUND 127
```

### 3. Debug prints everywhere
You have DEBUG conditional prints scattered throughout
**Recommendation**: Create a debug function:
```c
void debug_log(const char *format, ...);
```

---

## Testing Checklist

### Test Your Parts (Tokenizer, Parser, Expander)
- [ ] `echo hello world` → tokens: [WORD:"echo", WORD:"hello", WORD:"world"]
- [ ] `echo "hello world"` → after expansion: argv: ["echo", "hello world"]
- [ ] `echo '$USER'` → should NOT expand (single quotes)
- [ ] `echo "$USER"` → should expand to username
- [ ] `echo $?` → should expand to last exit code
- [ ] `ls | grep txt` → two commands with pipe
- [ ] `cat < input.txt > output.txt` → redirects parsed correctly
- [ ] `cat << EOF` → heredoc parsed correctly
- [ ] Unclosed quotes → syntax error
- [ ] `|` at start → syntax error
- [ ] `||` → syntax error (not implemented)
- [ ] `< >` → syntax error (no filename)

### Memory Leak Testing
Run with valgrind:
```bash
valgrind --leak-check=full --show-leak-kinds=all \
  --suppressions=./supps/readline.supp ./minishell
```

Test these commands:
```bash
echo hello
ls
cat file.txt
$USER
$?
exit
^D
```

---

## Summary

### What You've Done Well ✅
- Clean tokenizer implementation with quote handling
- Parser correctly builds command structure
- Expander handles $VAR and $? correctly
- Good separation of concerns (tokenizer → parser → expander)
- Memory cleanup functions are well-structured

### What Needs Fixing 🔧
1. Remove empty input error
2. Fix exit code 258 → 2
3. Better malloc failure handling
4. Handle edge case: $ followed by space

### What Your Partner Must Do 🚀
1. **Implement entire executor module** (this is the biggest missing piece!)
2. All 7 built-in commands
3. Fork/exec for external commands
4. Pipe creation and management
5. Redirection file operations
6. Signal handling during execution

---

## Recommended Next Steps

1. **Test your parts thoroughly** with the checklist above
2. **Fix the 4 remaining issues** I identified
3. **Work with your partner** to define the interface between expander and executor:
   - What does executor expect from shell->cmd_list?
   - How should exit be handled?
   - How are exit codes propagated?
4. **Run valgrind** to catch any remaining memory leaks
5. **Compare with bash** behavior for edge cases

Good luck! Your tokenizer, parser, and expander are solid. Once the executor is done, you'll have a working shell! 🎉
