/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:57:16 by aderraj           #+#    #+#             */
/*   Updated: 2023/11/18 22:20:38 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*s;
	const unsigned char	*d;

	if (n)
	{
		s = s1;
		d = s2;
		i = 0;
		while (i < n && s[i] == d[i])
			i++;
		if (i != n)
			return (s[i] - d[i]);
	}
	return (0);
}
