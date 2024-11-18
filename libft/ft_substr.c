/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 05:38:17 by aderraj           #+#    #+#             */
/*   Updated: 2023/11/18 01:31:39 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	sub_len;
	size_t	src_len;

	if (!s)
		return (NULL);
	sub_len = 0;
	if (start <= ft_strlen(s))
	{
		src_len = ft_strlen(s + start);
		sub_len = ((src_len >= len) * len) + ((src_len < len) * src_len);
	}
	ptr = malloc(sizeof(char) * (sub_len + 1));
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, s + start, sub_len);
	ptr[sub_len] = 0;
	return (ptr);
}
