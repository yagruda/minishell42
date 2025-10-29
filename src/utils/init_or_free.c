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

static char	**dup_envp(char **envp)
{
	char	**new_envp;
	int		i;
	int		len;

	len = 0;
	while (envp[len])
		len++;
	new_envp = malloc(sizeof(char *) * (len + 1));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			while (i-- > 0)
				free(new_envp[i]);
			free(new_envp);
			return (NULL);
		}
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

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
	shell->envp = dup_envp(envp);
	if (!shell->envp)
	{
		custom_error("Memory allocation for envp failed\n");
		free(shell);
		exit(EXIT_FAILURE);
	}
	shell->exit_code = 0;
	return (shell);
}

static void	free_envp(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	free_tokens(shell->tokens);
	free_commands(shell->cmd_list);
	free_envp(shell->envp);
	free(shell);
}
