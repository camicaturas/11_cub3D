/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri < cberneri@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2023/09/21 15:10:48 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;

	ptr = (char *)malloc(ft_strlen(s) + 1);
	if (ptr == NULL)
		return (NULL);
	ft_memcpy(ptr, s, ft_strlen(s) + 1);
	return (ptr);
}

/*
int main()
{
    char *src = "Hello, world!";
    char *duplicate = ft_strdup(src);
    if (duplicate != NULL)
    {
        printf("Original string: %s\n", src);
        printf("Duplicated string: %s\n", duplicate);
        free(duplicate);
    }
    else
    {
        printf("Memory allocation failed.\n");
    }
    return 0;
}
*/