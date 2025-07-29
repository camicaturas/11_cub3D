/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri < cberneri@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:09:57 by cberneri          #+#    #+#             */
/*   Updated: 2023/09/25 17:40:55 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t		altdst;
	size_t		i;

	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	while (dest[i] && i < size)
		i++;
	altdst = i;
	while (src[i - altdst] && i < size - 1)
	{
		dest[i] = src[i - altdst];
		i++;
	}
	if (altdst < size)
		dest[i] = '\0';
	return (altdst + ft_strlen(src));
}
/*
int main() {
 	char destin[20] = "";
	char source[20] = "";
	unsigned int result = ft_strlcat(destin, source, 1);
	printf("Result: %s\n", destin);
	printf("Length: %d\n", result);
	return (0);
}
*/