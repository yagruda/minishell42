/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:22:32 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/28 14:55:59 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
#define TOKENIZER_H


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

typedef struct s_redir
{
	int				type;   // REDIRECT_IN, REDIRECT_OUT, APPEND, HEREDOC
	char			*file;  // имя файла или delimiter
	struct s_redir	*next;
}	t_redir;


// t_cmd will be made after parsing 
typedef struct s_cmd
{
	char			**argv;   // аргументы команды: ["ls", "-la", NULL]
	t_redir			*redir;   // список редиректов	
	struct s_cmd	*next;    // следующая команда (если есть пайп)
}	t_cmd;

typedef struct s_shell
{
	t_token	*tokens;    // результат lexer
	t_cmd	*cmd_list;  // результат parser (перед expander и executor). EXpander переписывает ее.
	char	**envp;     // окружение
	int		exit_code;
}	t_shell;

void hide_ctrl_c(void);
void handle_sigint(int sig);
void handle_signals(void);
int quotes_closed(const char* input);
int is_empty(const char* input); 
int is_redirect_correct(const char* input);
int is_pipe_correct(const char *s);
int	is_builtin(char *cmd);

#endif