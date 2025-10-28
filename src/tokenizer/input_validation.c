/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 18:00:50 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/24 16:35:01 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// 1 - unclosed quotes found
// 0 - all quotes are closed
int quotes_closed(const char* input)
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
int is_empty(const char* input)
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

// VALID INPUTS:
// > s > s2 > s3 > s4 > s5 
// >>s >> s2 >> s2 >>s2 >>s2
// INVALID INPUTS:
// >>>s
// >
// ><, <>, >>>
// >|
// >          |

// checks for >< , <>, >>>, 
int	is_redirect_correct(const char *s)
{
	char p;

	while (*s)
	{
		if (*s == '>' || *s == '<')
		{
			p = *s;
			
			s++;
			
			if (!*s)
				return 0;
		
			if ((*s == '>' && p == '<') || (*s == '<' && p == '>') || (*s == '|'))
				return 0;
			else if (*s == p)
				s++;
				
			if(!*s || *s == '>' || *s == '<')
				return 0;
			
			while (*s && ft_isspace(*s))
			{
				s++;
			}
			
			if (*s == '|' || *s == '>' || *s == '<' || !*s)
				return 0;
		}
		else
			s++;
	}
	return 1;
}
/*
no consecutive pipes. even with spaces.  || or |   |
no pipes at the start or at the end. | cmd1 | cmd2 |

so, here has to be atleast one character at left and right side from the pipe.
*/
int is_pipe_correct(const char *s)
{
	// double check for safety. first check for empty input is done in main.
	if (!s)
		return 0;

	if (s[0] == '|' || s[ft_strlen_int(s)-1] == '|')
		return 0;
	
	while (*s)
	{
		if (*s == '|')
		{
			s++;
			if(!*s)
				return 0;	
			if (*s == '|')
				return 0;
			while (ft_isspace(*s))
				s++;
			if(!*s || *s == '|')
				return 0;
		}
		else
		{
			s++;
		}
	}
	return 1;
}

