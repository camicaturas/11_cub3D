/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri < cberneri@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2023/09/20 19:15:04 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*ptrdest;
	const unsigned char	*ptrsrc;
	size_t				i;

	ptrdest = (unsigned char *)dest;
	ptrsrc = (unsigned char *)src;
	i = 0;
	if (!dest && !src)
		return (NULL);
	if (ptrsrc < ptrdest)
	{
		while (++i <= n)
			ptrdest[n - i] = ptrsrc[n - i];
	}
	else
	{
		while (n-- > 0)
			*(ptrdest++) = *(ptrsrc++);
	}
	return (dest);
}

/*
int main()
{
   char dest[] = "oldstring";
   const char src[]  = "newstring";

   printf("Before memmove dest = %s, src = %s\n", dest, src);
   memmove(dest, src, 9);
   printf("After memmove dest = %s, src = %s\n\n", dest, src);

   char dest2[] = "oldstring";
   const char src2[]  = "newstring";

   printf("Before ft_memmove dest2 = %s, src2 = %s\n", dest2, src2);
   ft_memmove(dest2, src2, 9);
   printf("After ft_memmove dest2 = %s, src2 = %s\n", dest2, src2);

   return(0);
}
*/