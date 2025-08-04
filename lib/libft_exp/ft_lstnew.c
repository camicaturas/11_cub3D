/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri < cberneri@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:09:57 by cberneri          #+#    #+#             */
/*   Updated: 2023/09/21 15:42:32 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*memdest;

	memdest = (t_list *)malloc(sizeof(*memdest));
	if (memdest == NULL)
		return (NULL);
	memdest->content = content;
	memdest->next = NULL;
	return (memdest);
}

/*
int main (void)
{
char *a = "test";
printf("Result: %p", ft_lstnew(a));

}
*/