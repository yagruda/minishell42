/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 22:43:40 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/14 14:26:03 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



// CTRL+\ is  Process terminating with default action of signal 3 (SIGQUIT)
int main(int argc, char** argv, char** envp)
{
	char* input; 
	
	handle_signals();
	
	while(1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			free(input);
			break;
		}
		if (*input)
		{
			add_history(input);
		}
		if (ft_strcmp(input, "exit") == 0)
		{
			printf("exit\n");
			free(input);
			break;
		}

		if (ft_strcmp(input, "") != 0)
			printf("minishell: %s: command not found\n", input);
		
		free(input);
	}
	

	// free history that saves every readline run in memory.
	rl_clear_history();

	// it does after ctrl+d after exit written
	printf("program finished\n");

	(void)argc;
	(void)argv;
	(void)envp;

	return 0;
}

