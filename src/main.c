/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 22:43:40 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/28 19:33:44 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_input(t_shell *shell, char **argv)
{
	char	*input;

	(void)shell;
	(void)argv;
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			if (DEBUG)
				printf("CNTRL+D pressed\n");
			printf("exit\n");
			break ;
		}
		if (input)
		{
			process_input(shell, input, argv);
			free(input);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	if (argc > 1)
		custom_error("Arguments aren't supported\n");
	handle_signals();
	shell = init_shell(envp);
	handle_input(shell, argv);
	rl_clear_history();
	free_shell(shell);
	return (0);
}
