/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 22:43:40 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/28 16:10:45 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



// TBD: in main create and make basic t_shell structure to work with it
static void handle_input(t_shell *shell, char **argv)
{
	(void)shell;
	(void)argv;

	char* input;
	
	while (1)
	{
		input = readline("minishell> ");
		if (!input) 
		{
			if(DEBUG)
				printf("CNTRL+D pressed\n");
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
	t_shell* shell;
	if (argc > 1)
		custom_error("Arguments aren't supported\n");
	
	handle_signals();
	shell = init_shell(envp);
	handle_input(shell, argv);
	
	// it does after ctrl+d after exit written
	if (DEBUG)
		printf("program finished (delete me before final)\n");

	// now I have rl_clear_history in handle_input before exit, but in case of work, change it
	
	example_structures_init(shell);
	
	free_shell(shell);
	return 0;
}

