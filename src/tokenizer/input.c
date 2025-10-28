/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:42:23 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/28 16:09:57 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_syntax_errors(char *input, t_shell *shell)
{
	if (!quotes_closed(input))
	{
		custom_error("syntax error: unclosed quotes\n");
		shell->exit_code = 2;
		return (0);
	}
	if (!is_redirect_correct(input))
	{
		custom_error("syntax error near unexpected token `newline'\n");
		shell->exit_code = 2;
		return (0);
	}
	if (!(is_pipe_correct(input)))
	{
		custom_error("syntax error near unexpected token `|'\n");
		shell->exit_code = 2;
		return (0);
	}
	return (1);
}

int	input_is_valid(char *input, t_shell *shell)
{
	if (is_empty(input))
		return (0);
	return (check_syntax_errors(input, shell));
}

int	process_input(t_shell *shell, char *input, char **argv)
{
	(void)argv;
	if (*input)
		add_history(input);
	if (!input_is_valid(input, shell))
		return (0);
	tokenizer(shell, input);
	debug_print_tokens(shell->tokens);
	parser(shell);
	debug_print_commands(shell->cmd_list);
	expander(shell);
	if (DEBUG)
	{
		printf("=== After Expansion ===\n");
		debug_print_commands(shell->cmd_list);
	}
	executor(shell);
	cleanup_shell_after_cmd(shell);
	return (0);
}
