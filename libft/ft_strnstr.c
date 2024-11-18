/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:01:34 by aderraj           #+#    #+#             */
/*   Updated: 2023/11/18 19:47:21 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*needle)
		return ((char *)haystack);
	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j] && i + j < len)
		{
			if (!needle[j + 1])
				return ((char *)(haystack + i));
			j++;
		}
		i++;
	}
	return (NULL);
}
