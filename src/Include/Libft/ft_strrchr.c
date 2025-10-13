/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 12:16:35 by yhruda            #+#    #+#             */
/*   Updated: 2025/01/05 16:59:10 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*result;

	result = NULL;
	while (*s != '\0')
	{
		if (*s == (char)(c))
			result = (char *)s;
		s++;
	}
	if (c == '\0' && *s == '\0')
		return ((char *)s);
	return (result);
}

/* int main()
{
	char* str = "Hello";
	printf("%s\n", ft_strchr(str, 'p'));
	printf("%s\n", strrchr(str, 'p'));
	return (0);
} */