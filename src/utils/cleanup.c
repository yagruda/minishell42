/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:00:00 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/24 17:05:34 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Free all tokens in the list
void free_tokens(t_token *tokens)
{
	t_token *current;
	t_token *next;

	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}

// Free all redirects in the list
void free_redirects(t_redir *redir)
{
	t_redir *current;
	t_redir *next;

	current = redir;
	while (current)
	{
		next = current->next;
		if (current->file)
			free(current->file);
		free(current);
		current = next;
	}
}

// Free all commands in the list
void free_commands(t_cmd *cmd_list)
{
	t_cmd *current;
	t_cmd *next;
	int i;

	current = cmd_list;
	while (current)
	{
		next = current->next;
		
		// Free argv array
		if (current->argv)
		{
			i = 0;
			while (current->argv[i])
			{
				free(current->argv[i]);
				i++;
			}
			free(current->argv);
		}
		
		// Free redirects
		if (current->redir)
			free_redirects(current->redir);
		
		free(current);
		current = next;
	}
}

// Clean up shell structures after processing command
void cleanup_shell_after_cmd(t_shell *shell)
{
	if (shell->tokens)
	{
		free_tokens(shell->tokens);
		shell->tokens = NULL;
	}
	
	if (shell->cmd_list)
	{
		free_commands(shell->cmd_list);
		shell->cmd_list = NULL;
	}
}
