/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 21:39:11 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/19 21:47:02 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void debug_print_structures(t_shell *shell)
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

void example_structures_init(t_shell *shell)
{
    // Create sample tokens: "echo" "hello" "|" "grep" "h"
    t_token *tok1 = malloc(sizeof(t_token));
    tok1->value = strdup("echo");
    tok1->type = WORD;
    tok1->next = NULL;

    t_token *tok2 = malloc(sizeof(t_token));
    tok2->value = strdup("hello");
    tok2->type = WORD;
    tok2->next = NULL;
    tok1->next = tok2;

    t_token *tok3 = malloc(sizeof(t_token));
    tok3->value = strdup("|");
    tok3->type = PIPE;
    tok3->next = NULL;
    tok2->next = tok3;

    t_token *tok4 = malloc(sizeof(t_token));
    tok4->value = strdup("grep");
    tok4->type = WORD;
    tok4->next = NULL;
    tok3->next = tok4;

    t_token *tok5 = malloc(sizeof(t_token));
    tok5->value = strdup("h");
    tok5->type = WORD;
    tok5->next = NULL;
    tok4->next = tok5;

    shell->tokens = tok1;

    // Create sample redirections for first command: > output.txt
    t_redir *redir1 = malloc(sizeof(t_redir));
    redir1->type = REDIRECT_OUT;
    redir1->file = strdup("output.txt");
    redir1->next = NULL;

    // Create first command: echo hello > output.txt
    t_cmd *cmd1 = malloc(sizeof(t_cmd));
    cmd1->argv = malloc(sizeof(char *) * 3);
    cmd1->argv[0] = strdup("echo");
    cmd1->argv[1] = strdup("hello");
    cmd1->argv[2] = NULL;
    cmd1->redir = redir1;
    cmd1->next = NULL;

    // Create second command: grep h
    t_cmd *cmd2 = malloc(sizeof(t_cmd));
    cmd2->argv = malloc(sizeof(char *) * 3);
    cmd2->argv[0] = strdup("grep");
    cmd2->argv[1] = strdup("h");
    cmd2->argv[2] = NULL;
    cmd2->redir = NULL;
    cmd2->next = NULL;

    cmd1->next = cmd2;
    shell->cmd_list = cmd1;

    debug_print_structures(shell);
}