/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example_struct_debug.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 21:39:11 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/24 17:56:34 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	debug_print_structures(t_shell *shell)
{
	printf("Debug: Created sample structures\n");
	printf("  Tokens: %s %s %s %s %s\n",
		shell->tokens->value,
		shell->tokens->next->value,
		shell->tokens->next->next->value,
		shell->tokens->next->next->next->value,
		shell->tokens->next->next->next->next->value);
	printf("  First command: %s %s > %s\n",
		shell->cmd_list->argv[0],
		shell->cmd_list->argv[1],
		shell->cmd_list->redir->file);
	printf("  Second command: %s %s\n",
		shell->cmd_list->next->argv[0],
		shell->cmd_list->next->argv[1]);
}

static t_token	*create_token_chain(void)
{
	t_token	*tok1;
	t_token	*tok2;
	t_token	*tok3;
	t_token	*tok4;

	tok1 = malloc(sizeof(t_token));
	tok1->value = strdup("echo");
	tok1->type = WORD;
	tok2 = malloc(sizeof(t_token));
	tok2->value = strdup("hello");
	tok2->type = WORD;
	tok1->next = tok2;
	tok3 = malloc(sizeof(t_token));
	tok3->value = strdup("|");
	tok3->type = PIPE;
	tok2->next = tok3;
	tok4 = malloc(sizeof(t_token));
	tok4->value = strdup("grep");
	tok4->type = WORD;
	tok3->next = tok4;
	tok4->next = malloc(sizeof(t_token));
	tok4->next->value = strdup("h");
	tok4->next->type = WORD;
	tok4->next->next = NULL;
	return (tok1);
}

static t_cmd	*create_first_cmd(void)
{
	t_cmd	*cmd1;
	t_redir	*redir1;

	redir1 = malloc(sizeof(t_redir));
	redir1->type = REDIRECT_OUT;
	redir1->file = strdup("output.txt");
	redir1->next = NULL;
	cmd1 = malloc(sizeof(t_cmd));
	cmd1->argv = malloc(sizeof(char *) * 3);
	cmd1->argv[0] = strdup("echo");
	cmd1->argv[1] = strdup("hello");
	cmd1->argv[2] = NULL;
	cmd1->redir = redir1;
	cmd1->next = NULL;
	return (cmd1);
}

static t_cmd	*create_second_cmd(void)
{
	t_cmd	*cmd2;

	cmd2 = malloc(sizeof(t_cmd));
	cmd2->argv = malloc(sizeof(char *) * 3);
	cmd2->argv[0] = strdup("grep");
	cmd2->argv[1] = strdup("h");
	cmd2->argv[2] = NULL;
	cmd2->redir = NULL;
	cmd2->next = NULL;
	return (cmd2);
}

void	example_structures_init(t_shell *shell)
{
	t_cmd	*cmd1;
	t_cmd	*cmd2;

	shell->tokens = create_token_chain();
	cmd1 = create_first_cmd();
	cmd2 = create_second_cmd();
	cmd1->next = cmd2;
	shell->cmd_list = cmd1;
	if (DEBUG)
		debug_print_structures(shell);
}
