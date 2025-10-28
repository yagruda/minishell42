/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:30:00 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/24 17:13:32 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Get token type name for debugging
static const char *get_token_type_name(t_token_type type)
{
	if (type == WORD)
		return "WORD";
	else if (type == PIPE)
		return "PIPE";
	else if (type == REDIRECT_IN)
		return "REDIRECT_IN";
	else if (type == REDIRECT_OUT)
		return "REDIRECT_OUT";
	else if (type == APPEND)
		return "APPEND";
	else if (type == HEREDOC)
		return "HEREDOC";
	return "UNKNOWN";
}

// Print all tokens for debugging
void debug_print_tokens(t_token *tokens)
{
	t_token *current;
	int i;

	if (!DEBUG)
		return;
	
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

// Print all redirects for a command
static void debug_print_redirects(t_redir *redir)
{
	t_redir *current;
	int i;

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

// Print all commands for debugging
void debug_print_commands(t_cmd *cmd_list)
{
	t_cmd *current;
	int cmd_num;
	int i;

	if (!DEBUG)
		return;
	
	printf("\n=== DEBUG: COMMANDS ===\n");
	current = cmd_list;
	cmd_num = 0;
	while (current)
	{
		printf("Command[%d]:\n", cmd_num);
		
		// Print argv
		if (current->argv)
		{
			i = 0;
			while (current->argv[i])
			{
				printf("  argv[%d]: \"%s\"\n", i, current->argv[i]);
				i++;
			}
			if (i == 0)
				printf("  (no arguments)\n");
		}
		else
		{
			printf("  (argv is NULL)\n");
		}
		
		// Print redirects
		if (current->redir)
		{
			printf("  Redirections:\n");
			debug_print_redirects(current->redir);
		}
		else
		{
			printf("  (no redirections)\n");
		}
		
		printf("\n");
		current = current->next;
		cmd_num++;
	}
	printf("Total commands: %d\n", cmd_num);
	printf("=======================\n\n");
}

// Print shell state for debugging
void debug_print_shell(t_shell *shell)
{
	if (!DEBUG)
		return;
	
	printf("\n=== DEBUG: SHELL STATE ===\n");
	printf("Exit code: %d\n", shell->exit_code);
	printf("Tokens: %s\n", shell->tokens ? "present" : "NULL");
	printf("Commands: %s\n", shell->cmd_list ? "present" : "NULL");
	printf("==========================\n\n");
}
