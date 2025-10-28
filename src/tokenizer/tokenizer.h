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
# define TOKENIZER_H

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	HEREDOC
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	int				type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redir;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	t_token	*tokens;
	t_cmd	*cmd_list;
	char	**envp;
	int		exit_code;
}	t_shell;

void	hide_ctrl_c(void);
void	handle_sigint(int sig);
void	handle_signals(void);
int		quotes_closed(const char *input);
int		is_empty(const char *input);
int		is_redirect_correct(const char *input);
int		is_pipe_correct(const char *s);
int		is_builtin(char *cmd);
char	*skip_spaces(char *str);
char	*extract_word(char *str, int *len);
t_token	*create_token(char *value, t_token_type type);
void	add_token(t_token **head, t_token *new_token);

#endif
