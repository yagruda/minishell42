/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 22:45:04 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/28 14:28:04 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define DEBUG 0

# include "Include/ft_printf.h"
# include "tokenizer/tokenizer.h"
# include "parser/parser.h"
# include "utils/utils.h"
# include <termios.h>
# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>

void		custom_error(char *msg);
int			process_input(t_shell *shell, char *input, char **argv);
void		tokenizer(t_shell *shell, char *input);
void		parser(t_shell *shell);
void		expander(t_shell *shell);
char		*ft_strjoin_char(char *s, char c);
char		*get_env_value(char *var, t_shell *shell);
char		*extract_var_name(char *str, int *len);
char		*handle_var_expansion(char *str, int *i, t_shell *shell,
				char *result);
char		*handle_empty_var(char *result, char *var_name);
void		process_char(char *str, int *i, t_shell *shell, char **result);
char		*append_char(char *str, char c);
char		*append_str(char *s1, char *s2);
void		free_tokens(t_token *tokens);
void		free_redirects(t_redir *redir);
void		free_commands(t_cmd *cmd_list);
void		cleanup_shell_after_cmd(t_shell *shell);
void		debug_print_tokens(t_token *tokens);
void		debug_print_commands(t_cmd *cmd_list);
void		debug_print_shell(t_shell *shell);
const char	*get_token_type_name(t_token_type type);
void		debug_print_redirects(t_redir *redir);
void		print_cmd_info(t_cmd *cmd, int cmd_num);
void		example_structures_init(t_shell *shell);
void		executor(t_shell *shell);

#endif
