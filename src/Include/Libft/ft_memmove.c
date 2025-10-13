/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:02:39 by yhruda            #+#    #+#             */
/*   Updated: 2025/01/05 17:32:39 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*tmp;
	char	*dest;

	tmp = (char *)src;
	dest = (char *)dst;
	if (tmp < dest)
	{
		while (n--)
			dest[n] = tmp[n];
	}
	else
		ft_memcpy(dest, tmp, n);
	return (dst);
}

/*
int	main(void) {
	char src[] = "Hello, world!";
	char dest[20];
	// Example 1: Non-overlapping memory blocks
	printf("Before ft_memmove: dest = \"%s\"\n", dest);
	ft_memmove(dest, src, 13); // Copy the entire string from src to dest
	printf("After ft_memmove (non-overlapping): dest = \"%s\"\n", dest);
	// Example 2: Overlapping memory blocks
	char overlap_src[] = "123456789";
	printf("\nBefore ft_memmove (overlapping):
	overlap_src = \"%s\"\n", overlap_src);
	ft_memmove(overlap_src + 3, overlap_src, 6); // Move "456789"
	to start at overlap_src[3]
	printf("After ft_memmove (overlapping): overlap_src = \"%s\"\n",
	overlap_src);
	return (0);
}
*/