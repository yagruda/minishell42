# 🧠 What is fork()?
fork() is a system call that creates a new process by duplicating the current one.

The original process is called the parent.

The new process is called the child.

Both processes continue executing the same code after fork().

# 🔍 What does fork() return?
c
pid_t pid = fork();
In the parent process, fork() returns the PID of the child (a positive integer).

In the child process, fork() returns 0.

If fork() fails, it returns -1 in the parent, and no child is created.