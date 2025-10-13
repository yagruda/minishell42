/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formats.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 21:00:20 by yhruda            #+#    #+#             */
/*   Updated: 2025/03/04 21:02:49 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(int c)
{
	return (write(1, &c, 1));
}

int	print_str(char *str)
{
	int	count;

	count = 0;
	if (!str)
	{
		return (write(1, "(null)", 6));
	}
	while (*str != '\0')
	{
		print_char((int)*str);
		++str;
		++count;
	}
	return (count);
}

int	print_digit(unsigned long num, int base, int isUpperCase)
{
	int		count;
	char	*symbols;
	char	buffer[100];
	int		index;

	if (isUpperCase)
		symbols = "0123456789ABCDEF";
	else
		symbols = "0123456789abcdef";
	count = 0;
	index = 0;
	if (num == 0)
		buffer[index++] = '0';
	while (num)
	{
		buffer[index++] = symbols[num % base];
		num /= base;
	}
	while (index > 0)
	{
		print_char(buffer[--index]);
		count++;
	}
	return (count);
}

int	print_signed_digit(long num, int base)
{
	int	count;

	count = 0;
	if (num < 0)
	{
		count += write(1, "-", 1);
		num = -num;
	}
	count += print_digit((unsigned long)num, base, 0);
	return (count);
}

int	print_ptr(void *ptr)
{
	int	count;

	count = 0;
	count += write(1, "0x", 2);
	count += print_digit((unsigned long)ptr, 16, 0);
	return (count);
}
