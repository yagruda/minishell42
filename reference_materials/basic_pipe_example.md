# Basic Pipe Example in C

```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvlas <anvlas@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:24:49 by andrew            #+#    #+#             */
/*   Updated: 2025/10/22 10:41:12 by anvlas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	main(int argc, char *argv[])
{
	int	fd[2]; // the file descriptors get inherited by forked processes.
	int id;
	// fd[0]- read
	// fd[1] - write

	if (pipe(fd) == -1)
	{
		printf("An error ocurred with opening the pipe \n");
		return (1);
	}
	id = fork();
	if (id == 0)
	{
		// child process recieves 0
		int x;
		printf("Input a number: ");
		scanf("%d", &x);
		write(fd[1], &x, sizeof(int));
		close(fd[1]);
	}
	else
	{
		int y;
		close(fd[1]);
		read(fd[0], &y, sizeof(int));
		close(fd[0]);
		printf("Got from child process: %d \n", y);
		printf("Square of that is: %d \n", y * y);
	}
	return (0);
}
```
