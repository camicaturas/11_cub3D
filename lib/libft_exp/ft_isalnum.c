/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri < cberneri@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2023/09/20 15:34:15 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9')
		|| ((c >= 'A' && c <= 'Z')
			|| (c >= 'a' && c <= 'z')))
		return (1);
	return (0);
}

/*
int main(void)
{
	printf("the result is %d\n", (ft_isalnum('a')));
	printf("the result is %d\n", (ft_isalnum('3')));
	printf("the result is %d\n", (ft_isalnum('-')));

}
*/