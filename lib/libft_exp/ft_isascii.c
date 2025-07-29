/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri < cberneri@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2023/09/20 15:36:15 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/*
int main(void)
{
	printf("the result is %d\n", (ft_isascii('a')));
	printf("the result is %d\n", (ft_isascii('-')));
	printf("the result is %d\n", (ft_isascii('3')));
	printf("the result is %d\n", (ft_isascii(',')));
	printf("the result is %d\n", (ft_isascii(u'Ñ')));
	printf("the result is %d\n", (ft_isascii(u'‰')));
	printf("the result is %d\n", (ft_isascii(u'Š')));
	
}
*/