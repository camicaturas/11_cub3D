/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri < cberneri@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2024/01/16 19:39:05 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	printformat(va_list args, char format)
{
	int	print_length;

	print_length = 0;
	if (format == 'c')
		print_length += ft_printchar(va_arg(args, int));
	else if (format == 's')
		print_length += ft_printstr(va_arg(args, char *));
	else if (format == 'd' || format == 'i')
		print_length += ft_printdigit(va_arg(args, int), 10, 0);
	else if (format == 'p')
		print_length += ft_printptr(va_arg(args, unsigned long long));
	else if (format == 'u')
		print_length += ft_printdigit(va_arg(args, unsigned int), 10, 0);
	else if (format == 'x')
		print_length += ft_printdigit(va_arg(args, unsigned int), 16, 0);
	else if (format == 'X')
		print_length += ft_printdigit(va_arg(args, unsigned int), 16, 1);
	else if (format == '%')
		print_length += write(1, "%", 1);
	else
		print_length += write(1, &format, 1);
	return (print_length);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		charactercount;

	i = 0;
	charactercount = 0;
	va_start(args, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			charactercount += printformat(args, format[i + 1]);
			i++;
		}
		else
			charactercount += ft_printchar(format[i]);
		i++;
	}
	va_end(args);
	return (charactercount);
}
