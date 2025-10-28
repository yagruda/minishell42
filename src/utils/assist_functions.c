/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assist_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 16:17:17 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/24 14:57:28 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	if (c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	ft_strlen_int(const char *s)
{
	int	i;

	i = 0;
	while (*s)
	{
		i++;
		s++;
	}
	return (i);
}
