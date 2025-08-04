/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri < cberneri@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2023/09/20 19:27:21 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;
	size_t			i;

	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if ((ptr1[i] - ptr2[i]) < 0)
			return (-1);
		else if ((ptr1[i] - ptr2[i]) > 0)
			return (1);
		i++;
	}
	return (0);
}

/*
int main()
{
const char s1[] = "Camilo2";
const char s2[] = "Camilo4";
int result;

result = ft_memcmp(s1, s2, 7);
if (result < 0)
	printf("Result is: -1\n");
else if (result > 0)
	printf("Result is: 1\n");
else
	printf("Result is: 0\n");

return 0;
}
*/