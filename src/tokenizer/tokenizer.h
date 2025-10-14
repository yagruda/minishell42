/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:22:32 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/14 14:31:53 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
#define TOKENIZER_H

// to switch off showing contrling symbols (^C) using tcgetattr func
#include <termios.h>

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

//

void hide_ctrl_c(void);
void handle_sigint(int sig);
void handle_signals(void);

#endif