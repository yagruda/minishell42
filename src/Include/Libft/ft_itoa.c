/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:22:44 by yhruda            #+#    #+#             */
/*   Updated: 2025/01/05 17:22:39 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_num_length(int n)
{
	int	length;

	length = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		length++;
	while (n != 0)
	{
		n /= 10;
		length++;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;
	long	num;

	len = get_num_length(n);
	num = n;
	str = (char *)ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	while (--len >= 0 && str[len] != '-')
	{
		str[len] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}
/*
int	main(void)
{
	int		test_values[] = {0, 123, -123, 2147483647, -2147483648, -0};
	char	*result;

	for (int i = 0; i < 6; i++)
	{
		result = ft_itoa(test_values[i]);
		if (result)
		{
			printf("ft_itoa(%d) = %s\n", test_values[i], result);
			free(result);
		}
		else
		{
			printf("ft_itoa(%d) failed to allocate memory.\n", test_values[i]);
		}
	}
	return (0);
}
*/