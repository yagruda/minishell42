/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 22:43:40 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/12 23:01:29 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char** argv, char** envp)
{
	char* input; 
	
	while(1)
	{
		input = readline("minishell> ");
		if (!input)
			break;
		if (*input)
		{
			add_history(input);
			printf("You entered: %s\n", input);
		}
		free(input);
	}

	(void)argc;
	(void)argv;
	(void)envp;

	return 0;
}

