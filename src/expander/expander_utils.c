/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 18:30:00 by yhruda            #+#    #+#             */
/*   Updated: 2025/10/28 18:30:00 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_empty_var(char *result, char *var_name)
{
	char	*temp;

	temp = result;
	result = ft_strjoin_char(result, '$');
	free(temp);
	free(var_name);
	return (result);
}

char	*append_char(char *str, char c)
{
	char	*result;
	char	*temp;
	char	ch[2];

	ch[0] = c;
	ch[1] = '\0';
	temp = str;
	result = ft_strjoin(str, ch);
	free(temp);
	return (result);
}

char	*append_str(char *s1, char *s2)
{
	char	*result;
	char	*temp;

	temp = s1;
	result = ft_strjoin(s1, s2);
	free(temp);
	free(s2);
	return (result);
}
