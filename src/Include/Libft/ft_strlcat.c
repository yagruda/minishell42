/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:19:55 by yhruda            #+#    #+#             */
/*   Updated: 2025/01/06 14:31:23 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	if (!dst || !src)
		return (0);
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	if (dstsize <= dst_len)
		return (src_len + dstsize);
	while (src[i] != '\0' && dstsize - 1 > dst_len + i)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

/* int main()
{
	char	str1[20] = "Hello";
	char	str2[20] = "World";

	printf("Original %lu\n", strlcat(str1,str2, 12));
	printf("%s\n", str1);
	strcpy(str1, "Hello");
	printf("Custom %lu\n", ft_strlcat(str1,str2, 12));
	printf("%s\n", str1);
	return(0);
}
 */
