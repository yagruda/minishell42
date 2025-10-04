#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv, char **envp) {
    if (argc < 2) {
        write(2, "error: no command provided\n", 27);
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        write(2, "error: fatal\n", 13);
        return 1;
    } else if (pid == 0) {
        // Child process
        execve(argv[1], &argv[1], envp);
        write(2, "error: cannot execute ", 23);
        write(2, argv[1], strlen(argv[1]));
        write(2, "\n", 1);
        exit(1);
    } else {
        // Parent process
        waitpid(pid, NULL, 0);
    }

    return 0;
}
