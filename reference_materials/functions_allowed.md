
### 🧠 Allowed Functions for Shell Project

#### 📥 Input & Line Editing

| Function            | Description |
|---------------------|-------------|
| `readline`          | Reads a line of input from the user with editing and history support. |
| `rl_clear_history`  | Clears the readline history. |
| `rl_on_new_line`    | Prepares readline to handle a new line of input. |
| `rl_replace_line`   | Replaces the current line in the readline buffer. |
| `rl_redisplay`      | Refreshes the display of the current readline buffer. |
| `add_history`       | Adds a line to the readline history. |

#### 📤 Output & Messaging

| Function     | Description |
|--------------|-------------|
| `printf`     | Prints formatted output to stdout. |
| `write`      | Writes raw bytes to a file descriptor. |
| `perror`     | Prints a human-readable error message based on `errno`. |
| `strerror`   | Returns a string describing an error code. |

#### 🧠 Memory Management

| Function | Description |
|----------|-------------|
| `malloc` | Allocates memory dynamically. |
| `free`   | Frees previously allocated memory. |

#### 📁 File & Directory Access

| Function   | Description |
|------------|-------------|
| `access`   | Checks file permissions (e.g., executable). |
| `open`     | Opens a file and returns a file descriptor. |
| `read`     | Reads data from a file descriptor. |
| `close`    | Closes a file descriptor. |
| `unlink`   | Deletes a file. |
| `stat`     | Gets file metadata. |
| `lstat`    | Like `stat`, but works on symlinks. |
| `fstat`    | Gets metadata from an open file descriptor. |

#### 🧬 Process Control

| Function   | Description |
|------------|-------------|
| `fork`     | Creates a new process. |
| `wait`     | Waits for any child process to finish. |
| `waitpid`  | Waits for a specific child process. |
| `wait3`    | Waits for child and returns resource usage. |
| `wait4`    | Like `wait3`, with more control. |
| `execve`   | Replaces current process with a new program. |
| `exit`     | Terminates the current process. |
| `kill`     | Sends a signal to a process. |

#### ⚠️ Signal Handling

| Function       | Description |
|----------------|-------------|
| `signal`       | Sets a signal handler. |
| `sigaction`    | Advanced signal handling setup. |
| `sigemptyset`  | Initializes an empty signal set. |
| `sigaddset`    | Adds a signal to a signal set. |

#### 🌍 Environment & Terminal

| Function   | Description |
|------------|-------------|
| `getenv`   | Gets the value of an environment variable. |
| `isatty`   | Checks if a file descriptor is a terminal. |
| `ttyname`  | Gets the name of the terminal device. |
| `ttyslot`  | Returns the index of the current terminal slot. |
| `ioctl`    | Performs device-specific I/O operations. |

#### 📂 Directory Handling

| Function   | Description |
|------------|-------------|
| `opendir`  | Opens a directory stream. |
| `readdir`  | Reads entries from a directory. |
| `closedir` | Closes a directory stream. |

#### 📌 Working Directory

| Function | Description |
|----------|-------------|
| `getcwd` | Gets the current working directory. |
| `chdir`  | Changes the current working directory. |

#### 🎛️ Terminal Capabilities (termcap)

| Function     | Description |
|--------------|-------------|
| `tcsetattr`  | Sets terminal attributes. |
| `tcgetattr`  | Gets terminal attributes. |
| `tgetent`    | Loads terminal capability database. |
| `tgetflag`   | Gets a boolean terminal capability. |
| `tgetnum`    | Gets a numeric terminal capability. |
| `tgetstr`    | Gets a string terminal capability. |
| `tgoto`      | Computes cursor movement string. |
| `tputs`      | Outputs a terminal capability string. |

#### 🔀 File Descriptor Manipulation

| Function | Description |
|----------|-------------|
| `dup`    | Duplicates a file descriptor. |
| `dup2`   | Duplicates a file descriptor to a specific target. |
| `pipe`   | Creates a unidirectional data channel between processes. |

---