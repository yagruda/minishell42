/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 18:30:00 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/28 18:30:00 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_char(char *s, char c)
{
	char	*result;
	int		len;
	int		i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	result = malloc(len + 2);
	if (!result)
		return (NULL);
	i = 0;
	while (s[i])
	{
		result[i] = s[i];
		i++;
	}
	result[i] = c;
	result[i + 1] = '\0';
	return (result);
}

char	*get_env_value(char *var, t_shell *shell)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], var, len) == 0
			&& shell->envp[i][len] == '=')
			return (shell->envp[i] + len + 1);
		i++;
	}
	return ("");
}

char	*extract_var_name(char *str, int *len)
{
	int	i;

	if (str[0] == '?')
	{
		*len = 1;
		return (ft_strdup("?"));
	}
	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	*len = i;
	if (i == 0)
		return (ft_strdup(""));
	return (ft_substr(str, 0, i));
}

char	*handle_var_expansion(char *str, int *i, t_shell *shell, char *result)
{
	char	*var_name;
	char	*var_value;
	char	*temp;
	int		var_len;

	(*i)++;
	var_name = extract_var_name(&str[*i], &var_len);
	if (!var_name || var_len == 0)
		return (handle_empty_var(result, var_name));
	if (ft_strcmp(var_name, "?") == 0)
		var_value = ft_itoa(shell->exit_code);
	else
		var_value = ft_strdup(get_env_value(var_name, shell));
	temp = result;
	result = ft_strjoin(result, var_value);
	free(temp);
	free(var_name);
	free(var_value);
	*i += var_len;
	return (result);
}

void	process_char(char *str, int *i, t_shell *shell, char **result)
{
	char	*temp;

	if (str[*i] == '$' && str[*i + 1] && !ft_isspace(str[*i + 1]))
		*result = handle_var_expansion(str, i, shell, *result);
	else
	{
		temp = *result;
		*result = ft_strjoin_char(*result, str[*i]);
		free(temp);
		(*i)++;
	}
}
