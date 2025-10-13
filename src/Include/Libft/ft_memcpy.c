/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:18:48 by yhruda            #+#    #+#             */
/*   Updated: 2025/01/06 16:58:37 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*


		#include <string.h>

		void *
		memcpy(void *restrict dst, const void *restrict src, size_t n);

DESCRIPTION
		The memcpy() function copies n bytes from memory area src to memory
		area dst.  If dst and src overlap, behavior is undefined.
		Applications in which dst and src might overlap should use memmove(3)
		instead.

RETURN VALUES
		The memcpy() function returns the original value of dst.


*/

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	if (!dst && !src)
		return (NULL);
	i = 0;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

/*
int	main(void)
{
	char	origin[] = "HelloWorld";
	char	dest[10];

	ft_memcpy(dest, origin, sizeof(char) * 5);
	printf("%s", dest);
	return(0);
}
*/