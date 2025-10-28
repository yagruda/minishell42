/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_or_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 20:35:46 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/24 16:57:28 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
	{
		custom_error("Memory allocation for shell failed\n");
		exit(EXIT_FAILURE);
	}
	shell->tokens = NULL;
	shell->cmd_list = NULL;
	shell->envp = envp;
	shell->exit_code = 0;
	return (shell);
}

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	free_tokens(shell->tokens);
	free_commands(shell->cmd_list);
	free(shell);
}
