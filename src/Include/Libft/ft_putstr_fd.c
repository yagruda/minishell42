/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:28:44 by yhruda            #+#    #+#             */
/*   Updated: 2025/01/05 16:55:02 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
/*
int	main(void)
{
	char *str = "Hello, world!";
	ft_putstr_fd(str, 1); // Print string to standard output (stdout)
	write(1, "\n", 1);    // Add a newline after the output
	ft_putstr_fd(str, 2); // Print string to standard error (stderr)
	return (0);
}*/