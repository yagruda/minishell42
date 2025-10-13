/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 11:14:46 by yhruda            #+#    #+#             */
/*   Updated: 2025/01/06 14:29:42 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*arr;
	size_t	arr_length;

	if (nmemb != 0 && size != 0 && (nmemb * size) / nmemb != size)
		return (NULL);
	arr_length = nmemb * size;
	if (nmemb == 0 || size == 0)
		arr_length = 1;
	arr = malloc(arr_length);
	if (!arr)
		return (NULL);
	ft_memset(arr, 0, arr_length);
	return (arr);
}

/* int main()
{
	ft_calloc(5, 10);
	return (0);
} */