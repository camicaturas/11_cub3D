/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri < cberneri@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2023/09/20 15:42:24 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	totaldigits(int n)
{
	int	len;

	len = 0;
	if (n < 1)
		len++;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	*newstring(size_t n)
{
	char	*memdest;

	memdest = (char *)malloc(sizeof(char) * (n + 1));
	if (!memdest)
		return (NULL);
	return (memdest);
}

static long long	absnum(long long n)
{
	long long	num;

	num = 1;
	if (n < 0)
		num *= -n;
	else
		num *= n;
	return (num);
}

char	*ft_itoa(int n)
{
	char			*string;
	unsigned int	num;
	int				sign;
	int				length;

	sign = 0;
	if (n < 0)
		sign = 1;
	length = totaldigits(n);
	string = newstring(length);
	if (!string)
		return (NULL);
	*(string + length) = '\0';
	num = absnum(n);
	while (length--)
	{
		*(string + length) = 48 + num % 10;
		num = num / 10;
	}
	if (sign)
		*(string) = '-';
	return (string);
}

/*
int main()
{
	int a=154325;
	//char buffer[20];
	//itoa(a,buffer,2);   // here 2 means binary
	printf("value = %s\n", ft_itoa(a));
	
	//printf("Binary value = %s\n", buffer);
	//itoa(a,buffer,10);   // here 10 means decimal
	//printf("Decimal value = %s\n", buffer);

	//itoa(a,buffer,16);   // here 16 means Hexadecimal
 
 
	//printf("Hexadecimal value = %s\n", buffer);
	//ft_itoa(a);
	return 0;

}
*/
/*
int	main(void)
{
	int i = 0;
	int tab[5] = {-2147483648, -42, 0, 42, 2147483647};

	while (i < 5)
		printf("%s\n", ft_itoa(tab[i++]));
	return 0;

}

int	main(void)
{

	printf("%d\n", atoi("---1234ab567"));
	printf("%d\n", atoi("12s3334ab567"));
	printf("%d\n", atoi(" ---+--+1234ab567"));


	printf("%d\n", ft_atoi("---1234ab567"));
	printf("%d\n", ft_atoi("12s3334ab567"));
	printf("%d\n", ft_atoi(" ---+--+1234ab567"));
	return (0);
}
*/