/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri < cberneri@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2023/09/20 19:12:46 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptrsrc;
	unsigned char	*ptrdes;
	size_t			i;

	i = 0;
	ptrsrc = (unsigned char *)src;
	ptrdes = (unsigned char *)dest;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		ptrdes[i] = ptrsrc[i];
		i++;
	}
	return (dest);
}

/*
int main()
{
   const char src[50] = "Camilo Berneri";
   char dest[50];
   strcpy(dest,"Hello my friend!!");
   printf("Before memcpy dest = %s\n", dest);
   memcpy(dest, src, 9);
   printf("After memcpy dest = %s\n\n", dest);

   const char src2[50] = "Camilo Berneri";
   char dest2[50];
   strcpy(dest2,"Hello my friend!!");
   printf("Before ft_memcpy dest2 = %s\n", dest2);
   ft_memcpy(dest2, src2, 9);
   printf("After ft_memcpy dest2 = %s\n", dest2);
   return(0);
}
*/