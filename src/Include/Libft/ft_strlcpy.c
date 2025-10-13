/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:34:35 by yhruda            #+#    #+#             */
/*   Updated: 2025/01/06 14:30:12 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (dstsize > src_len + 1 && dstsize > 0)
		ft_memcpy(dst, src, src_len + 1);
	else if (dstsize > 0)
	{
		ft_memcpy(dst, src, dstsize - 1);
		dst[dstsize - 1] = 0;
	}
	return (src_len);
}

/* int main()
{
	char	src[20] = "Hello";
	char	dst[20];

	printf("%lu\n", ft_strlcpy(dst, src, 2));
	printf("%s\n", src);
	printf("%s\n", dst);
	return(0);
}
 */