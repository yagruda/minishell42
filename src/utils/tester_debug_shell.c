/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_debug_shell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:30:00 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/24 17:13:32 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static const char	*get_null_or_present(void *ptr)
{
	if (ptr)
		return ("present");
	return ("NULL");
}

void	debug_print_shell(t_shell *shell)
{
	if (!DEBUG)
		return ;
	printf("\n=== DEBUG: SHELL STATE ===\n");
	printf("Exit code: %d\n", shell->exit_code);
	printf("Tokens: %s\n", get_null_or_present(shell->tokens));
	printf("Commands: %s\n", get_null_or_present(shell->cmd_list));
	printf("==========================\n\n");
}

void	debug_print_commands(t_cmd *cmd_list)
{
	t_cmd	*current;
	int		cmd_num;

	if (!DEBUG)
		return ;
	printf("\n=== DEBUG: COMMANDS ===\n");
	current = cmd_list;
	cmd_num = 0;
	while (current)
	{
		print_cmd_info(current, cmd_num);
		current = current->next;
		cmd_num++;
	}
	printf("Total commands: %d\n", cmd_num);
	printf("=======================\n\n");
}
