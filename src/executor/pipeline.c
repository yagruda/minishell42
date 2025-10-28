/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 20:00:00 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/28 20:00:00 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "../builtins/builtins.h"

static void	execute_cmd_in_pipe(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	if (is_builtin(cmd->argv[0]))
	{
		shell->exit_code = exec_builtin(cmd, shell);
		exit(shell->exit_code);
	}
	path = find_command(cmd->argv[0], shell->envp);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	execve(path, cmd->argv, shell->envp);
	ft_putstr_fd("minishell: execution failed\n", 2);
	free(path);
	exit(126);
}

static void	setup_pipe_fd(int pipe_fd[2], int prev_fd, int is_last)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (!is_last)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
}

static pid_t	fork_and_exec(t_cmd *cmd, t_shell *shell, int p[2], int prev)
{
	pid_t	pid;
	int		is_last;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("minishell: fork failed\n", 2);
		return (-1);
	}
	if (pid == 0)
	{
		is_last = (cmd->next == NULL);
		setup_pipe_fd(p, prev, is_last);
		setup_redirects(cmd->redir, shell);
		execute_cmd_in_pipe(cmd, shell);
	}
	return (pid);
}

static int	process_cmd(t_cmd *cmd, t_shell *sh, int *p_fd, int *prev)
{
	int	pid;

	if (cmd->next && pipe(p_fd) == -1)
	{
		ft_putstr_fd("minishell: pipe failed\n", 2);
		return (-1);
	}
	pid = fork_and_exec(cmd, sh, p_fd, *prev);
	if (*prev != -1)
		close(*prev);
	if (cmd->next)
	{
		close(p_fd[1]);
		*prev = p_fd[0];
	}
	return (pid);
}

void	exec_pipeline(t_shell *shell)
{
	t_cmd	*cmd;
	int		pipe_fd[2];
	int		prev_fd;
	int		pids[1024];
	int		i;

	cmd = shell->cmd_list;
	prev_fd = -1;
	i = 0;
	while (cmd)
	{
		pids[i] = process_cmd(cmd, shell, pipe_fd, &prev_fd);
		if (pids[i] == -1)
			return ;
		cmd = cmd->next;
		i++;
	}
	wait_all_children(pids, i, shell);
}
