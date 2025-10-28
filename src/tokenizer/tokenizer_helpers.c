/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 18:30:00 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/28 18:30:00 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*skip_spaces(char *str)
{
	while (*str && ft_isspace(*str))
		str++;
	return (str);
}

char	*extract_word(char *str, int *len)
{
	int	i;
	int	in_squote;
	int	in_dquote;

	i = 0;
	in_squote = 0;
	in_dquote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (str[i] == '"' && !in_squote)
			in_dquote = !in_dquote;
		else if (!in_squote && !in_dquote)
		{
			if (ft_isspace(str[i]) || str[i] == '|'
				|| str[i] == '<' || str[i] == '>')
				break ;
		}
		i++;
	}
	*len = i;
	return (ft_substr(str, 0, i));
}

t_token	*create_token(char *value, t_token_type type)
{
	t_token	*token;

	if (!value)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
	{
		free(value);
		return (NULL);
	}
	token->value = value;
	token->type = type;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!new_token)
		return ;
	if (!*head)
	{
		*head = new_token;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_token;
}
