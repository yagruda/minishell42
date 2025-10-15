/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:42:23 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/15 19:04:45 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int input_is_valid(char* input)
{
	int i = 0;
	i = quotes_closed(input);
	if (i == 0)
	{
		custom_error("syntax error: unclosed quotes\n");
		// TBD: shell->exit_code = 258; 
		// TBD: mark is_valid = 0 in shell input struct
		return 0;
	}
	// TBD i = isnt_empty(input);
	// TBD i = has_valid_pipes(input);
	// TBD i = has_valid_redirects(input);

	return i;
}

void process_input(t_shell *shell, char* input, char** args)
{
	(void) shell;
	(void) args;
	if (input[0] != '\0')
		printf("input is not empty but not checked properly\n");
	else
		printf("empty input (works only if no spaces)\n"); // TBD: remove this line after testing is done

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