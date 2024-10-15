/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:55:39 by aderraj           #+#    #+#             */
/*   Updated: 2023/11/11 23:10:14 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	fill(char *s, long int n, int count)
{
	int	flag;

	flag = 0;
	s[count--] = 0;
	if (n < 0)
	{
		n *= -1;
		s[0] = '-';
		flag = 1;
	}
	else if (n == 0)
		s[count] = '0';
	while (count >= flag)
	{
		s[count--] = n % 10 + 48;
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	long int	d;
	int			count;
	char		*ptr;

	d = n;
	count = 0;
	if (n < 0)
	{
		d *= -1;
		count++;
	}
	else if (n == 0)
		count++;
	while (d > 0)
	{
		d /= 10;
		count++;
	}
	ptr = malloc(sizeof(char) * (count + 1));
	if (!ptr)
		return (NULL);
	fill(ptr, n, count);
	return (ptr);
}
