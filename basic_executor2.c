#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

// Resolves command using PATH
char *find_path(char *cmd) {
	char *path_env = getenv("PATH");
	if (!path_env)
		return NULL;

	char *paths = strdup(path_env);
	if (!paths)
		return NULL;

	char *dir = strtok(paths, ":");
	while (dir) {
		char full_path[1024];
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd);

		if (access(full_path, X_OK) == 0) 
		{
			free(paths);
			return strdup(full_path);
		}

		dir = strtok(NULL, ":");
	}

	free(paths);
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
		char *cmd_path = argv[1];
		if (!strchr(argv[1], '/')) {
			cmd_path = find_path(argv[1]);
			if (!cmd_path) {
				write(2, "error: command not found\n", 26);
				exit(1);
			}
		}

		execve(cmd_path, &argv[1], envp);
		write(2, "error: cannot execute ", 23);
		write(2, argv[1], strlen(argv[1]));
		write(2, "\n", 1);
		exit(1);
	} else {
		waitpid(pid, NULL, 0);
	}

	return 0;
}
