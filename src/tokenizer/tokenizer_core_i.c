/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_core_i.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:25:20 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/28 18:30:00 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*process_redirect_in(char **input, t_shell *shell)
{
	t_token	*token;

	if (*(*input + 1) == '<')
	{
		token = create_token(ft_strdup("<<"), HEREDOC);
		*input += 2;
	}
	else
	{
		token = create_token(ft_strdup("<"), REDIRECT_IN);
		(*input)++;
	}
	add_token(&shell->tokens, token);
	return (*input);
}

static char	*process_redirect_out(char **input, t_shell *shell)
{
	t_token	*token;

	if (*(*input + 1) == '>')
	{
		token = create_token(ft_strdup(">>"), APPEND);
		*input += 2;
	}
	else
	{
		token = create_token(ft_strdup(">"), REDIRECT_OUT);
		(*input)++;
	}
	add_token(&shell->tokens, token);
	return (*input);
}

static char	*process_token(char *input, t_shell *shell)
{
	int		len;
	char	*word;
	t_token	*token;

	if (*input == '|')
	{
		token = create_token(ft_strdup("|"), PIPE);
		add_token(&shell->tokens, token);
		input++;
	}
	else if (*input == '<')
		input = process_redirect_in(&input, shell);
	else if (*input == '>')
		input = process_redirect_out(&input, shell);
	else
	{
		word = extract_word(input, &len);
		token = create_token(word, WORD);
		add_token(&shell->tokens, token);
		input += len;
	}
	return (input);
}

void	tokenizer(t_shell *shell, char *input)
{
	input = skip_spaces(input);
	while (*input)
	{
		input = process_token(input, shell);
		input = skip_spaces(input);
	}
}
