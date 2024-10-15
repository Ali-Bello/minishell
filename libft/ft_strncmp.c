/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:57:38 by aderraj           #+#    #+#             */
/*   Updated: 2023/11/18 19:42:54 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n)
	{
		i = 0;
		while (s1[i] && s2[i] && i < n)
		{
			if ((unsigned char)(s1[i]) == (unsigned char)(s2[i]))
				i++;
			else
				break ;
		}
		if (n != i)
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}
