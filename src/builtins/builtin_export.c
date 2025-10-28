/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 20:00:00 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/28 20:00:00 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	print_export(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(shell->envp[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

static int	find_env_var(char **envp, char *var, int len)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, len) == 0 && envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static char	**add_env_var(char **envp, char *new_var)
{
	char	**new_envp;
	int		i;
	int		len;

	len = 0;
	while (envp[len])
		len++;
	new_envp = malloc(sizeof(char *) * (len + 2));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_envp[i] = envp[i];
		i++;
	}
	new_envp[i] = ft_strdup(new_var);
	new_envp[i + 1] = NULL;
	free(envp);
	return (new_envp);
}

static int	update_env_var(t_shell *shell, char *arg)
{
	char	*eq;
	int		idx;
	int		len;

	eq = ft_strchr(arg, '=');
	if (!eq)
		return (0);
	len = eq - arg;
	idx = find_env_var(shell->envp, arg, len);
	if (idx >= 0)
	{
		free(shell->envp[idx]);
		shell->envp[idx] = ft_strdup(arg);
	}
	else
		shell->envp = add_env_var(shell->envp, arg);
	return (0);
}

int	builtin_export(char **argv, t_shell *shell)
{
	int	i;

	if (!argv[1])
	{
		print_export(shell);
		return (0);
	}
	i = 1;
	while (argv[i])
	{
		update_env_var(shell, argv[i]);
		i++;
	}
	return (0);
}
