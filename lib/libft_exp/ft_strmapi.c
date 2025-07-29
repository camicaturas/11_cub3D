/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri < cberneri@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2023/09/21 15:20:16 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int		i;
	char				*memdest;

	if (!s)
		return (NULL);
	memdest = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (memdest == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		memdest[i] = f(i, s[i]);
		i++;
	}
	memdest[i] = '\0';
	return (memdest);
}
/*
char modify_char(unsigned int index, char c)
{
	// Add 1 to the ASCII value of the character at index 'index'
	return c + (char)index;
}

int main()
{
	char my_string[] = "Hello, World!";
	ft_strmapi(my_string, modify_char);
	return 0;
}
*/