/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:56:33 by yhruda            #+#    #+#             */
/*   Updated: 2025/01/06 11:58:30 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	The memchr() function locates the first occurrence of c (converted to an
		unsigned char) in string s.

	RETURN VALUES
		The memchr() function returns a pointer to the byte located, or NULL if
		no such byte exists within n bytes.
*/

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n > 0)
	{
		if (*(const unsigned char *)s == (unsigned char)c)
			return ((void *)s);
		s++;
		n--;
	}
	return (NULL);
}

/* int main()
{
	char* arr = "Helloxc4g";
	printf("%s", ft_memchr(arr, 'x', 8));
	return (0);
} */