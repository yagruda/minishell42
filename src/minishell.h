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
#define MINISHELL_H

#define DEBUG 1

#include "Include/ft_printf.h" // containts libft.h inside as well
#include "tokenizer/tokenizer.h"
#include "parser/parser.h"
#include "utils/utils.h"

// to switch off showing contrling symbols (^C) using tcgetattr func
#include <termios.h>

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

//errors.c
void custom_error(char *msg);
int process_input(t_shell *shell, char *input, char **argv);

// tokenizer_core_i.c
void tokenizer(t_shell *shell, char *input);

// parser_core_i.c
void parser(t_shell *shell);

// expander_i.c
void expander(t_shell *shell);

// cleanup.c
void free_tokens(t_token *tokens);
void free_redirects(t_redir *redir);
void free_commands(t_cmd *cmd_list);
void cleanup_shell_after_cmd(t_shell *shell);

// debug.c
void debug_print_tokens(t_token *tokens);
void debug_print_commands(t_cmd *cmd_list);
void debug_print_shell(t_shell *shell);

// FOR DEBUG PURPOSES ONLY
void example_structures_init(t_shell *shell);

#endif