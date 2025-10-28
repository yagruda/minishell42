/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 20:00:00 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/28 20:00:00 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	wait_all_children(int *pids, int count, t_shell *shell)
{
	int	i;
	int	status;

	i = 0;
	while (i < count)
	{
		if (pids[i] > 0)
		{
			waitpid(pids[i], &status, 0);
			if (i == count - 1)
			{
				if (WIFEXITED(status))
					shell->exit_code = WEXITSTATUS(status);
				else if (WIFSIGNALED(status))
					shell->exit_code = 128 + WTERMSIG(status);
			}
		}
		i++;
	}
}
