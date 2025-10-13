/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:28:14 by yhruda            #+#    #+#             */
/*   Updated: 2025/01/05 16:54:53 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
/*
int	main(void)
{
	// Example 1: Write to standard output
	ft_putchar_fd('H', 1); // Prints: H
	ft_putchar_fd('\n', 1); // Prints: (newline)
	// Example 2: Write to standard error
	ft_putchar_fd('E', 2); // Prints: E to stderr
	ft_putchar_fd('\n', 2); // Prints: (newline) to stderr
	return(0);
}*/