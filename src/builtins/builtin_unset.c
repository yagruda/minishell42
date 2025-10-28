/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 20:00:00 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/28 20:00:00 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	find_var_idx(char **envp, char *var)
{
	int	i;
	int	len;

	len = ft_strlen(var);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, len) == 0 && envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static void	remove_env_var(char **envp, int idx)
{
	free(envp[idx]);
	while (envp[idx + 1])
	{
		envp[idx] = envp[idx + 1];
		idx++;
	}
	envp[idx] = NULL;
}

int	builtin_unset(char **argv, t_shell *shell)
{
	int	i;
	int	idx;

	if (!argv[1])
		return (0);
	i = 1;
	while (argv[i])
	{
		idx = find_var_idx(shell->envp, argv[i]);
		if (idx >= 0)
			remove_env_var(shell->envp, idx);
		i++;
	}
	return (0);
}
