/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_i.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 16:37:04 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/24 17:56:59 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_var_value(char *str, int *i, t_shell *shell)
{
	char	*var_name;
	char	*var_value;
	int		var_len;

	(*i)++;
	var_name = extract_var_name(&str[*i], &var_len);
	if (ft_strcmp(var_name, "?") == 0)
		var_value = ft_itoa(shell->exit_code);
	else
		var_value = ft_strdup(get_env_value(var_name, shell));
	free(var_name);
	*i += var_len;
	return (var_value);
}

static char	*expand_vars(char *str, t_shell *shell)
{
	char	*result;
	int		i;
	int		in_sq;

	result = ft_strdup("");
	i = 0;
	in_sq = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_sq)
			in_sq = 1;
		else if (str[i] == '\'' && in_sq)
			in_sq = 0;
		if (str[i] == '$' && !in_sq && str[i + 1])
			result = append_str(result, get_var_value(str, &i, shell));
		else
			result = append_char(result, str[i++]);
	}
	free(str);
	return (result);
}

static char	*remove_quotes(char *str)
{
	char	*result;
	int		i;
	char	quote;

	result = ft_strdup("");
	i = 0;
	quote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && quote == 0)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		else
			result = append_char(result, str[i]);
		i++;
	}
	free(str);
	return (result);
}

static void	process_args(t_cmd *cmd, t_shell *shell)
{
	int	i;

	i = 0;
	while (cmd->argv && cmd->argv[i])
	{
		cmd->argv[i] = expand_vars(cmd->argv[i], shell);
		cmd->argv[i] = remove_quotes(cmd->argv[i]);
		i++;
	}
}

void	expander(t_shell *shell)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = shell->cmd_list;
	while (cmd)
	{
		process_args(cmd, shell);
		redir = cmd->redir;
		while (redir)
		{
			redir->file = expand_vars(redir->file, shell);
			redir->file = remove_quotes(redir->file);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
