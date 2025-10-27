
# dup2() 
The **dup2()**  function is a system call in C (on Unix-like operating systems) 
that duplicates an existing file descriptor onto a specified new file descriptor number.

Its primary use is for I/O redirection within a program, especially when 
implementing shell features like piping or file redirection.

So, your program can write to file instead of printing out on the screen result of programm you are running.

The function signature is:

```
#include <unistd.h>
int dup2(int oldfd, int newfd);

```
---
### How dup2() Works
The dup2() call performs two key actions atomically (as a single, uninterrupted operation):

- Closes the Target: If the newfd is currently an open file descriptor, it is silently closed first.

- Duplicates the Source: It makes the newfd refer to the same open file description as the oldfd.

In simpler terms, it forces the file descriptor number newfd to become an alias for the file pointed to by oldfd.

### YOUTUBE 
[fd, dup(), dup2() system call tutorial](https://www.youtube.com/watch?v=EqndHT606Tw)