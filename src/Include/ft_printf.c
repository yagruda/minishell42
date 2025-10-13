/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhruda <yhruda@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:46:26 by yhruda            #+#    #+#             */
/*   Updated: 2025/03/04 20:58:02 by yhruda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_format(char specifier, va_list *ap)
{
	int	count;

	count = 0;
	if (specifier == 'c')
		count += print_char(va_arg(*ap, int));
	else if (specifier == 's')
		count += print_str(va_arg(*ap, char *));
	else if (specifier == 'd' || specifier == 'i')
		count += print_signed_digit((long)va_arg(*ap, int), 10);
	else if (specifier == 'u')
		count += print_digit((unsigned long)va_arg(*ap, unsigned int), 10, 0);
	else if (specifier == 'x')
		count += print_digit((unsigned long)va_arg(*ap, unsigned int), 16, 0);
	else if (specifier == 'X')
		count += print_digit((unsigned long)va_arg(*ap, unsigned int), 16, 1);
	else if (specifier == '%')
		count += print_char('%');
	else if (specifier == 'p')
		count += print_ptr(va_arg(*ap, void *));
	else
		count += write(1, &specifier, 1);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	va_start(ap, format);
	count = 0;
	while (*format != '\0')
	{
		if (*format == '%')
			count += print_format(*(++format), &ap);
		else
			count += write(1, format, 1);
		++format;
	}
	va_end(ap);
	return (count);
}

/*  int main()
{
	ft_printf("Pointer link is %p\n", -3);
	return (0);
}

 */
