/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 20:00:00 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/28 20:00:00 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../minishell.h"

int		builtin_echo(char **argv);
int		builtin_cd(char **argv, t_shell *shell);
int		builtin_pwd(void);
int		builtin_export(char **argv, t_shell *shell);
int		builtin_unset(char **argv, t_shell *shell);
int		builtin_env(t_shell *shell);
int		builtin_exit(char **argv, t_shell *shell);

#endif
