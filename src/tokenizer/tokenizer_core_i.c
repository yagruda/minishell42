/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_core_i.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:25:20 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/28 15:44:10 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Helper: Skip whitespace
static char *skip_spaces(char *str)
{
    while (*str && ft_isspace(*str))
        str++;
    return str;
}

// Helper: Extract word until delimiter
static char *extract_word(char *str, int *len)
{
    int i = 0;
    int in_squote = 0;
    int in_dquote = 0;

    while (str[i])
    {
        if (str[i] == '\'' && !in_dquote)
            in_squote = !in_squote;
        else if (str[i] == '"' && !in_squote)
            in_dquote = !in_dquote;
        else if (!in_squote && !in_dquote)
        {
            if (ft_isspace(str[i]) || str[i] == '|' || 
                str[i] == '<' || str[i] == '>')
                break;
        }
        i++;
    }
    *len = i;
    return ft_substr(str, 0, i);
}

// Create new token
static t_token *create_token(char *value, t_token_type type)
{
    t_token *token = malloc(sizeof(t_token));
    if (!token)
        return NULL;
    token->value = value;
    token->type = type;
    token->next = NULL;
    return token;
}

// Add token to end of list
static void add_token(t_token **head, t_token *new_token)
{
    t_token *current;

    if (!*head)
    {
        *head = new_token;
        return;
    }
    current = *head;
    while (current->next)
        current = current->next;
    current->next = new_token;
}

// Main tokenizer function
void tokenizer(t_shell *shell, char *input)
{
    int len;
    char *word;
    t_token *token;

    input = skip_spaces(input);
    while (*input)
    {
        if (*input == '|')
        {
            token = create_token(ft_strdup("|"), PIPE);
            add_token(&shell->tokens, token);
            input++;
        }
        else if (*input == '<')
        {
            if (*(input + 1) == '<')
            {
                token = create_token(ft_strdup("<<"), HEREDOC);
                input += 2;
            }
            else
            {
                token = create_token(ft_strdup("<"), REDIRECT_IN);
                input++;
            }
            add_token(&shell->tokens, token);
        }
        else if (*input == '>')
        {
            if (*(input + 1) == '>')
            {
                token = create_token(ft_strdup(">>"), APPEND);
                input += 2;
            }
            else
            {
                token = create_token(ft_strdup(">"), REDIRECT_OUT);
                input++;
            }
            add_token(&shell->tokens, token);
        }
        else
        {
            word = extract_word(input, &len);
            token = create_token(word, WORD);
            add_token(&shell->tokens, token);
            input += len;
        }
        input = skip_spaces(input);
    }
}

