/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:09:57 by cberneri          #+#    #+#             */
/*   Updated: 2025/06/03 14:27:05 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;
	size_t			i;

	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	i = 0;
	while ((ptr1[i] || ptr2[i]) && i < n)
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
int main () {
   char str1[15];
   char str2[15];
   int ret;
   int ret2;

   strcpy(str1, "Camilo2");
   strcpy(str2, "Camilo1");

   ret = strncmp(str1, str2, 7);
   ret2 = ft_strncmp(str1, str2, 7);

   if(ret < 0) {
      printf("str1 is less than str2\n");
   } else if(ret > 0) {
      printf("str2 is less than str1\n");
   } else {
      printf("str1 is equal to str2\n");
   }

   if(ret2 < 0) {
      printf("str1 is less than str2\n");
   } else if(ret2 > 0) {
      printf("str2 is less than str1\n");
   } else {
      printf("str1 is equal to str2\n");
   }
   
   return(0);
}
*/