#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

// This program just runs another programm, passed as argument.
// it doesn't require full path. 
// it tries to find comand in bin, and if finds, runs it. 
// a.out ls

char *next_token(const char *src, int *pos) {
    int start = *pos;
    int len = 0;

    while (src[start] == ':')
        start++;

    int i = start;
    while (src[i] && src[i] != ':') {
        len++;
        i++;
    }

    if (len == 0)
        return NULL;

    char *token = malloc(len + 1);
    if (!token)
        return NULL;

    for (int j = 0; j < len; j++)
        token[j] = src[start + j];
    token[len] = '\0';

    *pos = src[i] ? i + 1 : i; // Move past colon
    return token;
}

// concatinates path by writing to dest (dir + / + comand)
void join_path(char *dest, const char *dir, const char *comand) {
	int i = 0;

	while (dir[i]) {
		dest[i] = dir[i];
		i++;
	}
	dest[i++] = '/';
	int j = 0;
	while (comand[j]) {
		dest[i++] = comand[j++];
	}
	dest[i] = '\0';
}

// Finds correct path for a command 
char *find_path(char *comand) {
    char *path_env = getenv("PATH");
    if (!path_env)
        return NULL;

    int pos = 0;
    char *dir;

    while ((dir = next_token(path_env, &pos))) 
	{
        char full_path[1024];
        join_path(full_path, dir, comand);

        if (access(full_path, X_OK) == 0) {
            free(dir);
            return strdup(full_path);
        }

        free(dir);
    }

    return NULL;
}


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
		// Resolve path if command doesn't contain '/'
		char *comand_path = argv[1];
		if (!strchr(argv[1], '/')) {
			comand_path = find_path(argv[1]);
			if (!comand_path) {
				write(2, "error: command not found\n", 26);
				exit(1);
			}
		}

		execve(comand_path, &argv[1], envp);
		write(2, "error: cannot execute ", 23);
		write(2, argv[1], strlen(argv[1]));
		write(2, "\n", 1);
		exit(1);
	} else {
		waitpid(pid, NULL, 0);
	}

	return 0;
}

// execve - allowed
// waitpid - allowed
// getenv	- allowed
// snprintf - not
// strchr 	- not
// strtok	- not
// strdup	- not
