/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:27:18 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/24 17:56:32 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	custom_error(char *msg)
{
	rl_replace_line("", 0);
	rl_on_new_line();
	while (*msg)
	{
		if (*msg == '\n')
			write(STDERR_FILENO, "\n", 1);
		else
			write(STDERR_FILENO, msg, 1);
		msg++;
	}
}
