/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 20:45:24 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/24 14:57:22 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//assist_functions.c
int ft_isspace(char c);
int	ft_strlen_int(const char *s);

// init_or_free.c
t_shell* init_shell(char **envp);
void free_shell(t_shell *shell);
