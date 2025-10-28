/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 20:00:00 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/28 20:00:00 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../minishell.h"

void	executor(t_shell *shell);
int		is_builtin(char *cmd);
int		exec_builtin(t_cmd *cmd, t_shell *shell);
char	*find_command(char *cmd, char **envp);
void	setup_redirects(t_redir *redir, t_shell *shell);
void	exec_single_cmd(t_cmd *cmd, t_shell *shell);
void	exec_pipeline(t_shell *shell);
void	wait_all_children(int *pids, int count, t_shell *shell);

#endif
