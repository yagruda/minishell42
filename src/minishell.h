/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 22:45:04 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/15 18:31:43 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "Include/ft_printf.h" // containts libft.h inside as well
#include "tokenizer/tokenizer.h"
#include "parser/parser.h"

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
void process_input(t_shell *shell, char *input, char **argv);


#endif