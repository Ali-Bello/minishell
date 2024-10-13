/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 20:05:20 by aderraj           #+#    #+#             */
/*   Updated: 2024/10/13 06:22:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../LEXER/lexer.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if ((dst != src))
	{
		while (i < n)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	len;

	len = ft_strlen(s1) + 1;
	ptr = malloc(len * sizeof(char));
	if (!ptr)
		return (NULL);
	return ((char *)ft_memcpy(ptr, s1, len));
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t	len2;
	char	*ptr;

	if (!s1 || !s2)
	{
		if (s1)
			return (ft_strdup(s1));
		else if (s2)
			return (ft_strdup(s2));
		else
			return (ft_strdup(""));
	}
	len = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ptr = malloc(sizeof(char) * (len + len2 + 1));
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, s1, len);
	ft_memcpy(ptr + len, s2, len2);
	ptr[len + len2] = 0;
	return (ptr);
}

void    word_parser(t_list **node)
{
    (*node)->s = expand_and_remove_quotes((*node)->s);
}
void    parser(t_list *list)
{
    t_list *tmp;
    int i;

    tmp = list;
    while (tmp)
    {
        if (tmp->type == WORD)
            word_parser(&tmp);
        tmp = tmp->next;
    }
}

int main()
{
    char    *buf = readline(BLUE"$$:"RESET);
    t_list *list = lexer(buf);
    parser(list);
    for (t_list *tmp = list;  tmp; tmp = tmp->next)
        printf("node {s->[%s], type = [%d]}\n", tmp->s, tmp->type);
    return (0);
}