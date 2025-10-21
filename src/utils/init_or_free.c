/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_or_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 20:35:46 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/19 22:36:51 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_shell* init_shell(char **envp)
{
	t_shell *shell;
	
	shell = malloc(sizeof(t_shell));
	if(!shell)
	{
		custom_error("Memory allocation for shell failed\n");
		exit(EXIT_FAILURE);
	}
	
	shell->tokens = NULL;
	shell->cmd_list = NULL;
	shell->envp = envp;
	shell->exit_code = 0;
	
	return shell;
}


// while (tok) wouldn't work if tok is NULL at the beginning
static void free_tokens(t_token *tok)
{
    t_token *next;
	
    while (tok) 
    {
        next = tok->next;
        free(tok->value);
        free(tok);
        tok = next;
		printf("did some free tokens\n"); // FOR DEBUGGING ONLY, DELETE LATER
    }
}

static void free_redirs(t_redir *r)
{
    t_redir *next;
    while (r)
    {
        next = r->next;
        free(r->file);
        free(r);
        r = next;
		printf("did some free redirs\n"); // FOR DEBUGGING ONLY, DELETE LATER
    }
}

static void free_cmds(t_cmd *cmd)
{
    t_cmd *next;
    while (cmd)
    {
        next = cmd->next;

        if (cmd->argv)
        {
            for (size_t i = 0; cmd->argv[i]; ++i)
                free(cmd->argv[i]);
            free(cmd->argv);
			printf("did some free cmd argv\n"); // FOR DEBUGGING ONLY, DELETE LATER
        }
        free_redirs(cmd->redir);
		printf("did some free cmd redirs\n"); // FOR DEBUGGING ONLY, DELETE LATER
        free(cmd);
		printf("did some free cmd\n"); // FOR DEBUGGING ONLY, DELETE LATER
        cmd = next;
    }
}

// Why free for all items? bc free(shell) only frees "the box", not its contents.
void free_shell(t_shell *shell)
{
    if (!shell)
        return;

    free_tokens(shell->tokens);
    free_cmds(shell->cmd_list);
    // Do NOT free(shell->envp); it's not owned.
    free(shell);
}
