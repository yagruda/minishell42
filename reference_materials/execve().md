// ctr +shift + V to see md preview

# execve
**execve()** is the system call that actually runs a new program in place of the current one. In a minishell, it's the key to executing external commands like ls, cat, or echo.

## 🧠 Why You Need execve in a Minishell
When your shell parses a command like ls -l, it needs to:

Create a new process to run ls without killing the shell itself.

Replace the child process’s memory with the ls program.

Let the parent shell wait for the child to finish.

This is done using:

fork() → creates a new process (child).

execve() → replaces the child’s memory with the new program.

waitpid() → lets the parent wait for the child to finish.

Without execve, your shell wouldn’t actually run external programs—it would just sit there pretending.
## 📌 Key Points About execve
Prototype:  ```int execve(const char *pathname, char *const argv[], char *const envp[]);```

- pathname: Full path to the executable (e.g., /bin/ls)

- argv: Argument list (first is usually the program name)

- envp: Environment variables (can pass environ or NULL)

## 🧪 Common Pitfalls
If execve fails, it returns -1 and sets errno. Always check with perror().

It does not return on success. The current process is replaced.

You must fork() first—never call execve in the main shell process unless you want to kill your shell.

## Youtube explanation:
[Using execve in C](https://www.youtube.com/watch?v=iq7puCxsgHQ)