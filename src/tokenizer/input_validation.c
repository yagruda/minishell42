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

int	quotes_closed(const char *input)
{
	int	i;
	int	single_quote;
	int	double_quote;

	(void)input;
	i = 0;
	single_quote = 0;
	double_quote = 0;
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
		return (0);
	return (1);
}

int	is_empty(const char *input)
{
	while (*input)
	{
		if (!ft_isspace(*input))
			return (0);
		input++;
	}
	return (1);
}

static int	check_redirect_symbol(const char **s, char p)
{
	if ((**s == '>' && p == '<') || (**s == '<' && p == '>') || (**s == '|'))
		return (0);
	else if (**s == p)
		(*s)++;
	if (!**s || **s == '>' || **s == '<')
		return (0);
	while (**s && ft_isspace(**s))
		(*s)++;
	if (**s == '|' || **s == '>' || **s == '<' || !**s)
		return (0);
	return (1);
}

int	is_redirect_correct(const char *s)
{
	char	p;

	while (*s)
	{
		if (*s == '>' || *s == '<')
		{
			p = *s;
			s++;
			if (!*s)
				return (0);
			if (!check_redirect_symbol(&s, p))
				return (0);
		}
		else
			s++;
	}
	return (1);
}

int	is_pipe_correct(const char *s)
{
	if (!s)
		return (0);
	if (s[0] == '|' || s[ft_strlen_int(s) - 1] == '|')
		return (0);
	while (*s)
	{
		if (*s == '|')
		{
			s++;
			if (!*s)
				return (0);
			if (*s == '|')
				return (0);
			while (ft_isspace(*s))
				s++;
			if (!*s || *s == '|')
				return (0);
		}
		else
			s++;
	}
	return (1);
}
