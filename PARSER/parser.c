/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 20:05:20 by aderraj           #+#    #+#             */
/*   Updated: 2024/10/11 05:12:10 by marvin           ###   ########.fr       */
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


char    *get_varname(char *s, int *j)
{
    int i;

    i = 0;
    while (s[i] && !isspace(s[i]) && (isalnum(s[i]) || s[i] == '_'))
        i++;
    *j = i;
    return (ft_strndup(s, i));
}

char *expand_var(char *s, int *i)
{
    char *var_name;
    char *value;
    char *holder;
    int idx;

    // Get the variable name starting after the '$'
    var_name = get_varname(&s[*i + 1], &idx);
    // Get the value of the environment variable (if it exists)
    value = getenv(var_name);
    // Join the beginning part of the string with the variable value and the rest of the string
    holder = ft_strjoin(ft_strndup(s, *i), value);
    holder = ft_strjoin(holder, &s[*i + idx + 1]);

    free(var_name);
    free(s);
    *i += idx + 1;

    return holder;
}



void    parser(t_list *list)
{
    t_list *tmp;

    tmp = list;
    while (tmp)
    {
        if (tmp->type == WORD)
        {
            int i = 0;
            int flag = 0;
            while (tmp->s[i])
            {
                if (tmp->s[i] == '$' && !flag)
                    tmp->s = expand_var(tmp->s, &i);
                if (tmp->s[i] == '\'' && !flag)
                    flag = 1;
                else if (tmp->s[i] =='\'' && flag)
                    flag = 0;
                i++;
            }
        }
        tmp = tmp->next;
    }

}

int main()
{
    char    *buf = readline("Minishell:>");
    t_list *list = lexer(buf);
    parser(list);
    for (t_list *tmp = list;  tmp; tmp = tmp->next)
        printf("node {s->[%s], idx = [%d],  type = [%d]}\n", tmp->s, tmp->idx, tmp->type);
    return (0);
}