/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 20:00:00 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/28 20:00:00 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void handle_input_redir(char *file, t_shell *shell) {
  int fd;

  fd = open(file, O_RDONLY);
  if (fd == -1) {
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(file, 2);
    ft_putstr_fd(": No such file or directory\n", 2);
    shell->exit_code = 1;
    exit(1);
  }
  dup2(fd, STDIN_FILENO);
  close(fd);
}

static void handle_output_redir(char *file, int append, t_shell *shell) {
  int fd;

  if (append)
    fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
  else
    fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (fd == -1) {
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(file, 2);
    ft_putstr_fd(": Permission denied\n", 2);
    shell->exit_code = 1;
    exit(1);
  }
  dup2(fd, STDOUT_FILENO);
  close(fd);
}

static void handle_heredoc(char *delimiter) {
  int fd[2];
  char *line;

  if (pipe(fd) == -1) {
    perror("minishell");
    exit(1);
  }
  while (1) {
    line = readline("> ");
    if (!line || ft_strcmp(line, delimiter) == 0) {
      free(line);
      break;
    }
    ft_putstr_fd(line, fd[1]);
    ft_putstr_fd("\n", fd[1]);
    free(line);
  }
  close(fd[1]);
  dup2(fd[0], STDIN_FILENO);
  close(fd[0]);
}

void setup_redirects(t_redir *redir, t_shell *shell) {
  while (redir) {
    if (redir->type == REDIRECT_IN)
      handle_input_redir(redir->file, shell);
    else if (redir->type == REDIRECT_OUT)
      handle_output_redir(redir->file, 0, shell);
    else if (redir->type == APPEND)
      handle_output_redir(redir->file, 1, shell);
    else if (redir->type == HEREDOC)
      handle_heredoc(redir->file);
    redir = redir->next;
  }
}
