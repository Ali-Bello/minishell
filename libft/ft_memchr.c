/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:57:14 by aderraj           #+#    #+#             */
/*   Updated: 2023/11/18 19:43:07 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	if (n)
	{
		i = 0;
		while (i < n)
		{
			if (((unsigned char *)s)[i] == (unsigned char)c)
				return ((void *)(s + i));
			i++;
		}
	}
	return (NULL);
}
