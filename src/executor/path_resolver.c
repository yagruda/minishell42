/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_resolver.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 20:00:00 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/28 20:00:00 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static char	*get_path_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*join_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(dir, "/");
	path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (path);
}

static char	*search_in_path(char **dirs, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (dirs[i])
	{
		full_path = join_path(dirs[i], cmd);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_command(char *cmd, char **envp)
{
	char	*path_env;
	char	**dirs;
	char	*result;
	int		i;

	if (!cmd || !cmd[0])
		return (NULL);
	if (ft_strchr(cmd, '/') != NULL)
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = get_path_env(envp);
	if (!path_env)
		return (NULL);
	dirs = ft_split(path_env, ':');
	if (!dirs)
		return (NULL);
	result = search_in_path(dirs, cmd);
	i = 0;
	while (dirs[i])
		free(dirs[i++]);
	free(dirs);
	return (result);
}
