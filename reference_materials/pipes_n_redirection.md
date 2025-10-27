## **Youbube videos relevant to pipes**
#### The best youtube explanation on how it works in linux, and what it needed for:
[linux terminal: pipes and redirection](https://www.youtube.com/watch?v=oyc_6UfoW3w)

#### coding pipes in c:
https://www.youtube.com/watch?v=6xbLgZpOBi8&t=31s  - using pipe(), fork(), waitpid(), execlp

[executing programs with code](https://www.youtube.com/watch?v=HAN_kCJyrOc)  - discussing exec type of functions.

[communicating between proceses using pipes](https://www.youtube.com/watch?v=Mqb2dVRe0uo)  - basic piping must watch!

---
In the C programming language, the **`pipe()`** function is used to create a **pipe**, which is a mechanism for **interprocess communication (IPC)**. A pipe allows data to flow in one direction between two related processes (such as a parent and a child process).

---

## **How `pipe()` Works**

### **Function Signature**
```c
#include <unistd.h>

int pipe(int pipefd[2]); //pipe need to recieve array of 2 int
```
- **`pipefd`**: is array of two integers. After a successful call:
  - `pipefd[0]` is the **file descriptor for reading** from the pipe.
  - `pipefd[1]` is the **file descriptor for writing** to the pipe.

### **Return Value**
- On success, `pipe()` returns `0`.
- On failure, it returns `-1` and sets `errno` to indicate the error.

---
### **using the pipe**
- You can use **read()** and **write()** functions to use pipe.
- each process need to close unused end of pipe.

---

## **Key Characteristics of Pipes**
- **Unidirectional**: Data flows from `pipefd[1]` (write end) to `pipefd[0]` (read end).
- **FIFO (First-In-First-Out)**: The order of data written is preserved when read.
- **Buffering**: The kernel buffers the data, so the reader and writer do not need to be synchronized.
- **Process Relationship**: Typically used between a parent and child process after a `fork()`.

---

## **Example Usage**

```c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int pipefd[2];
    char buffer[20];
    pid_t pid;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {    // Child process
        close(pipefd[1]); // Close unused write end
        read(pipefd[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
        close(pipefd[0]);
    } else {           // Parent process
        close(pipefd[0]); // Close unused read end
        write(pipefd[1], "Hello, child!", 13);
        close(pipefd[1]);
    }

    return 0;
}
```

### **What Happens Here?**
1. A pipe is created.
2. The parent process writes "Hello, child!" to the pipe.
3. The child process reads the message from the pipe and prints it.

---

## **Important Notes**
- **Close Unused Ends**: Always close the file descriptors you are not using in each process to avoid deadlocks.
- **Blocking Behavior**: By default, `read()` blocks until data is available, and `write()` blocks until the pipe has space.
- **No Seek**: Pipes are sequential; you cannot use `lseek()` on them.

---

**Want to see a more complex example or have questions about using pipes with multiple processes?**