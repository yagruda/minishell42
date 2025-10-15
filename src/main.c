/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 22:43:40 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/15 18:49:18 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// TBD: in main create and make basic t_shell structure to work with it
void handle_input(t_shell *shell, char **argv)
{
	(void)shell;
	(void)argv;

	char* input;
	
	while (1)
	{
		input = readline("minishell> ");
		if (!input) //
		{
			printf("exit\n");
			free(input);
			break;
		}
		if(input)
		{
			process_input(shell, input, argv);
			free(input);
		}
		else
		{
			rl_clear_history();
		// TBD:	free_shell(shell);
			exit(EXIT_SUCCESS);
		}
	}
	
}
// maybe tbd free input after processing it


int main(int argc, char** argv, char** envp)
{
	(void)argc;
	(void)argv;
	(void)envp;

	if (argc > 1)
		custom_error("Arguments aren't supported\n");
	
	handle_signals();
	handle_input(NULL, argv);
	
	// it does after ctrl+d after exit written
	printf("program finished (delete me before final)\n");

	// now I have rl_clear_history in handle_input before exit, but in case of work, change it
	
	return 0;
}

