/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 11:54:48 by yhruda            #+#    #+#             */
/*   Updated: 2025/01/05 16:55:08 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*new;
	int		i;

	i = 0;
	new = (char *)malloc(sizeof(char) * ft_strlen(src) + 1);
	if (new == NULL)
	{
		return (NULL);
	}
	while (*src)
	{
		new[i++] = *src++;
	}
	new[i] = '\0';
	return (new);
}

/* int	main(void)
{
	return (0);
} */