/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:22:32 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/14 18:02:26 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
#define TOKENIZER_H

// to switch off showing contrling symbols (^C) using tcgetattr func
#include <termios.h>

void hide_ctrl_c(void);
void handle_sigint(int sig);
void handle_signals(void);


typedef enum e_token_type
{
	WORD,           // common word or argument
	PIPE,           // |
	REDIRECT_IN,    // <
	REDIRECT_OUT,   // >
	APPEND,         // >>
	HEREDOC         // <<
}	t_token_type;

// this struct would be used only in tokenizer part! It would be freed at Parser stage, so at Execution stage wouldn't get it. 
typedef struct s_token
{
	char* value; 
	t_token_type type;
	struct s_token* next;
}	t_token;

typedef struct s_shell
{
	t_token	*tokens;    // результат lexer
	t_cmd	*cmd_list;  // результат parser (перед expander и executor). EXpander переписывает ее.
	char	**envp;     // окружение
	int		exit_status;
}	t_shell;

#endif