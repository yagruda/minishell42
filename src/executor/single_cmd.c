/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 20:00:00 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/28 20:00:00 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins/builtins.h"
#include "executor.h"

static void execute_external_cmd(t_cmd *cmd, t_shell *shell) {
  char *path;

  path = find_command(cmd->argv[0], shell->envp);
  if (!path) {
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(cmd->argv[0], 2);
    ft_putstr_fd(": command not found\n", 2);
    free_shell(shell);
    exit(127);
  }
  execve(path, cmd->argv, shell->envp);
  ft_putstr_fd("minishell: ", 2);
  ft_putstr_fd(cmd->argv[0], 2);
  ft_putstr_fd(": command execution failed\n", 2);
  free(path);
  free_shell(shell);
  exit(126);
}

static void exec_in_child(t_cmd *cmd, t_shell *shell) {
  signal(SIGQUIT, SIG_DFL);
  setup_redirects(cmd->redir, shell);
  if (is_builtin(cmd->argv[0])) {
    shell->exit_code = exec_builtin(cmd, shell);
    free_shell(shell);
    exit(shell->exit_code);
  }
  execute_external_cmd(cmd, shell);
}

void exec_single_cmd(t_cmd *cmd, t_shell *shell) {
  pid_t pid;
  int status;

  if (!cmd->argv || !cmd->argv[0])
    return;
  if (is_builtin(cmd->argv[0]) && !cmd->redir) {
    shell->exit_code = exec_builtin(cmd, shell);
    return;
  }
  pid = fork();
  if (pid == -1) {
    ft_putstr_fd("minishell: fork failed\n", 2);
    return;
  }
  if (pid == 0)
    exec_in_child(cmd, shell);
  waitpid(pid, &status, 0);
  if (WIFEXITED(status))
    shell->exit_code = WEXITSTATUS(status);
  else if (WIFSIGNALED(status))
    shell->exit_code = 128 + WTERMSIG(status);
}
