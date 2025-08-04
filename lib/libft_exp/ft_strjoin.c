/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri < cberneri@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:32:44 by cberneri          #+#    #+#             */
/*   Updated: 2023/09/21 15:14:49 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*mem;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	mem = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (mem == NULL)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		mem[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2))
	{
		mem[i] = s2[j];
		i++;
		j++;
	}
	mem[i] = '\0';
	return (mem);
}
/*
int main(void) 
{
	char	*src1;
	char	*src2;
	
	src1 = "Camilo";
	src2 = " Berneri";
	
//ft_strjoin(src1, src2);
	printf("Result: %s\n", ft_strjoin(src1, src2));
}
*/