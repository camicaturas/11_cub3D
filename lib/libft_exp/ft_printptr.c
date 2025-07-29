/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri < cberneri@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 19:29:10 by cberneri          #+#    #+#             */
/*   Updated: 2024/01/16 19:35:46 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_putptr(uintptr_t num)
{
	char	*chars;
	int		value;

	value = 0;
	chars = "0123456789abcdef";
	if (num >= 16)
	{
		value += ft_putptr(num / 16);
		value += ft_putptr(num % 16);
	}
	else
		value += write(1, &chars[num], 1);
	return (value);
}

int	ft_printptr(unsigned long long ptr)
{
	int	value;

	value = 0;
	if (!ptr)
		value += write(1, "(nil)", 5);
	else
	{
		value += ft_printstr("0x");
		value += ft_putptr(ptr);
	}
	return (value);
}
