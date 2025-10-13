/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 20:58:06 by yhruda            #+#    #+#             */
/*   Updated: 2025/01/06 14:30:23 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* DESCRIPTION
		The memcmp() function compares byte string s1 against byte string s2.
		Both strings are assumed to be n bytes long.

RETURN VALUES
		The memcmp() function returns zero if the two strings are identical,
		otherwise returns the difference between the first two differing bytes
		(treated as unsigned char values, so that ‘\200’ is greater than ‘\0’,
		for example).  Zero-length strings are always identical.  This behavior
		is not required by C and portable code should only depend on the sign of
		the returned value. */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (n != 0)
	{
		if (*(const unsigned char *)s1 != *(const unsigned char *)s2)
			return (*(const unsigned char *)s1 - *(unsigned char *)s2);
		n--;
		s1++;
		s2++;
	}
	return (0);
}

/* int main()
{
	char* arr = "Helloxc41";
	char* arr2 = "Helloxc4g";
	printf("%d", ft_memcmp(arr, arr2, 8));
	return (0);
}  */