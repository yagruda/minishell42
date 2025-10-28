/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:30:00 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/24 17:13:32 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

const char	*get_token_type_name(t_token_type type)
{
	if (type == WORD)
		return ("WORD");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == REDIRECT_IN)
		return ("REDIRECT_IN");
	else if (type == REDIRECT_OUT)
		return ("REDIRECT_OUT");
	else if (type == APPEND)
		return ("APPEND");
	else if (type == HEREDOC)
		return ("HEREDOC");
	return ("UNKNOWN");
}

void	debug_print_tokens(t_token *tokens)
{
	t_token	*current;
	int		i;

	if (!DEBUG)
		return ;
	printf("\n=== DEBUG: TOKENS ===\n");
	current = tokens;
	i = 0;
	while (current)
	{
		printf("Token[%d]: type=%-15s value=\"%s\"\n",
			i, get_token_type_name(current->type), current->value);
		current = current->next;
		i++;
	}
	printf("Total tokens: %d\n", i);
	printf("=====================\n\n");
}

void	debug_print_redirects(t_redir *redir)
{
	t_redir	*current;
	int		i;

	current = redir;
	i = 0;
	while (current)
	{
		printf("    Redir[%d]: type=%-15s file=\"%s\"\n",
			i, get_token_type_name(current->type), current->file);
		current = current->next;
		i++;
	}
}

static void	print_argv(char **argv)
{
	int	i;

	if (argv)
	{
		i = 0;
		while (argv[i])
		{
			printf("  argv[%d]: \"%s\"\n", i, argv[i]);
			i++;
		}
		if (i == 0)
			printf("  (no arguments)\n");
	}
	else
		printf("  (argv is NULL)\n");
}

void	print_cmd_info(t_cmd *cmd, int cmd_num)
{
	printf("Command[%d]:\n", cmd_num);
	print_argv(cmd->argv);
	if (cmd->redir)
	{
		printf("  Redirections:\n");
		debug_print_redirects(cmd->redir);
	}
	else
		printf("  (no redirections)\n");
	printf("\n");
}
