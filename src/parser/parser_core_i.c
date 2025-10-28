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

// Create new command
static t_cmd *create_cmd(void)
{
    t_cmd *cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return NULL;
    cmd->argv = NULL;
    cmd->redir = NULL;
    cmd->next = NULL;
    return cmd;
}

// Add redirect to command
static void add_redirect(t_cmd *cmd, char *file, t_token_type type)
{
    t_redir *new_redir = malloc(sizeof(t_redir));
    if (!new_redir)
        return;
    t_redir *current;


    new_redir->type = type;
    new_redir->file = strdup(file);
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

// Add argument to command
static void add_arg(t_cmd *cmd, char *arg)
{
    int i = 0;
    char **new_argv;

    while (cmd->argv && cmd->argv[i])
        i++;
    new_argv = malloc(sizeof(char *) * (i + 2));
    if (!new_argv)
        return;
    i = 0;
    while (cmd->argv && cmd->argv[i])
    {
        new_argv[i] = cmd->argv[i];
        i++;
    }
    new_argv[i] = ft_strdup(arg);
    new_argv[i + 1] = NULL;
    free(cmd->argv);
    cmd->argv = new_argv;
}

// Main parser
void parser(t_shell *shell)
{
    t_token *token = shell->tokens;
    t_cmd *current_cmd = create_cmd();
    t_cmd *first_cmd = current_cmd;

    while (token)
    {
        if (token->type == PIPE)
        {
            current_cmd->next = create_cmd(); 
            current_cmd = current_cmd->next;
        }
        else if (token->type == REDIRECT_IN || token->type == REDIRECT_OUT ||
                 token->type == APPEND || token->type == HEREDOC)
        {
            /* save redirect type before advancing to filename */
            t_token_type redir_type = token->type;
            token = token->next; // Move to filename
            if (token)
                add_redirect(current_cmd, token->value, redir_type);
        }
        else if (token->type == WORD)
        {
            add_arg(current_cmd, token->value);
        }
        token = token->next;
    }
    shell->cmd_list = first_cmd;
}
