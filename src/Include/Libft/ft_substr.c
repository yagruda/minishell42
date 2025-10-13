/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:08:51 by yhruda            #+#    #+#             */
/*   Updated: 2025/01/06 16:37:00 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Prototype char *ft_substr(char const *s, unsigned int start,
size_t len);
Turn in files-
Parameters s: The string from which to create the substring.
start: The start index of the substring in the
string ’s’.
len: The maximum length of the substring.
Return value The substring.
NULL if the allocation fails.
External functs. malloc
Description Allocates (with malloc(3)) and returns a substring
from the string ’s’.
The substring begins at index ’start’ and is of
maximum size ’len’. */

#include "libft.h"

static char	*ft_empty_string(void)
{
	char	*arr;

	arr = (char *)malloc(1);
	if (!arr)
		return (NULL);
	arr[0] = '\0';
	return (arr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	char	*arr;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	size = ft_strlen(s);
	if (len > size - start)
		len = size - start;
	if (start >= size)
		return (ft_empty_string());
	arr = (char *)malloc((len + 1) * sizeof(char));
	if (!arr)
		return (NULL);
	while (s[start + i] && i < len)
	{
		arr[i] = s[start + i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

/* int main()
{
	char* str = "Hello World";
	printf("%s \n", ft_substr("Bonjour ca va?", 5, 8));
	return(0);
} */