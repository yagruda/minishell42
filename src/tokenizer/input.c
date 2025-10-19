/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:42:23 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/19 20:39:54 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int input_is_valid(char* input)
{
	if (!quotes_closed(input))
	{
		custom_error("syntax error: unclosed quotes\n");
		// TBD: shell->exit_code = 258; 
		// TBD: mark is_valid = 0 in shell input struct
		return 0;
	}
	if (is_empty(input))
	{
		custom_error("syntax error: empty input\n");
		// TBD: shell->exit_code = 258;
		// TBD: mark is_valid = 0 in shell input struct
		return 0;
	}
	
	// TBD i = has_valid_pipes(input);
	// TBD i = has_valid_redirects(input);

	return 1;
}

void process_input(t_shell *shell, char* input, char** args)
{
	(void) shell;
	(void) args;

	if (input_is_valid(input))
	{
		add_history(input);
		// TBD: tokenizer(shell,input);
	}
	else
	{
		
		return;
	}
	
	// TBD: call parser here
	
	
	

	// FOR DEBUGGING ONLY, DELETE LATER
	if (ft_strcmp(input, "") != 0)
		printf("minishell: %s: command not found\n", input);

	// TBD: parser(shell,input);
	// TBD: input = process_continuation(shell,input); wtf is continuation? 
	
}