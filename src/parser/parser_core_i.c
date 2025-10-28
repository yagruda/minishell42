/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_core_i.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 23:19:06 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/28 16:00:25 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

static void	add_redirect(t_cmd *cmd, char *file, t_token_type type)
{
	t_redir	*new_redir;
	t_redir	*current;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return ;
	new_redir->type = type;
	new_redir->file = ft_strdup(file);
	if (!new_redir->file)
	{
		free(new_redir);
		return ;
	}
	new_redir->next = NULL;
	if (!cmd->redir)
		cmd->redir = new_redir;
	else
	{
		current = cmd->redir;
		while (current->next)
			current = current->next;
		current->next = new_redir;
	}
}

static void	add_arg(t_cmd *cmd, char *arg)
{
	int		i;
	char	**new_argv;

	i = 0;
	while (cmd->argv && cmd->argv[i])
		i++;
	new_argv = malloc(sizeof(char *) * (i + 2));
	if (!new_argv)
		return ;
	i = 0;
	while (cmd->argv && cmd->argv[i])
	{
		new_argv[i] = cmd->argv[i];
		i++;
	}
	new_argv[i] = ft_strdup(arg);
	if (!new_argv[i])
	{
		free(new_argv);
		return ;
	}
	new_argv[i + 1] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
}

static t_token	*process_redirection(t_token *token, t_cmd *cmd)
{
	t_token_type	redir_type;

	redir_type = token->type;
	token = token->next;
	if (token)
		add_redirect(cmd, token->value, redir_type);
	return (token);
}

void	parser(t_shell *shell)
{
	t_token	*token;
	t_cmd	*current_cmd;
	t_cmd	*first_cmd;

	token = shell->tokens;
	current_cmd = create_cmd();
	first_cmd = current_cmd;
	while (token)
	{
		if (token->type == PIPE)
		{
			current_cmd->next = create_cmd();
			current_cmd = current_cmd->next;
		}
		else if (token->type == REDIRECT_IN || token->type == REDIRECT_OUT
			|| token->type == APPEND || token->type == HEREDOC)
			token = process_redirection(token, current_cmd);
		else if (token->type == WORD)
			add_arg(current_cmd, token->value);
		if (token)
			token = token->next;
	}
	shell->cmd_list = first_cmd;
}
