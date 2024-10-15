/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:57:29 by aderraj           #+#    #+#             */
/*   Updated: 2023/11/18 19:38:07 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	re;

	i = 0;
	j = 0;
	re = 0;
	if (dstsize)
	{
		j = ft_strlen(dst);
		if (j > dstsize)
			re = dstsize;
		else
			re = j;
		while (j < dstsize - 1 && src[i])
			dst[j++] = src[i++];
		dst[j] = 0;
	}
	return (re + ft_strlen(src));
}
