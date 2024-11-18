/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 00:29:39 by aderraj           #+#    #+#             */
/*   Updated: 2023/11/18 23:18:40 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	j = ft_strlen(s1);
	j -= (j > 0);
	while (ft_strchr(set, s1[j]) && j > 0)
		j--;
	ptr = ft_substr(s1, i, j - i + 1);
	if (!ptr)
		return (NULL);
	return (ptr);
}
