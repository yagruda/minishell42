/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validaiton.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 18:00:50 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/19 20:45:00 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// 1 - unclosed quotes found
// 0 - all quotes are closed
int quotes_closed(char* input)
{
	(void) input;
	int i = 0;
	int single_quote = 0;
	int double_quote = 0;
	
	while (input[i])
	{
		if (input[i] == '\'' && single_quote == 0)
			single_quote++;
		else if (input[i] == '\'' && single_quote >= 1)
			single_quote--;
		else if (input[i] == '\"' && double_quote == 0)
			double_quote++;
		else if (input[i] == '\"' && double_quote >= 1)
			double_quote--;
		i++;
	}
	if (single_quote > 0 || double_quote > 0)
		return 0; 
	return 1;
}
int is_empty(char* input)
{
	while (*input)
	{
		if (!ft_isspace(*input))
			return 0;
		input++;
	}
	return 1;
	// TBD
}