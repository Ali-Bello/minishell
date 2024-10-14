/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 04:05:37 by marvin            #+#    #+#             */
/*   Updated: 2024/10/14 04:05:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../LEXER/lexer.h"

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

char *get_prefix_suffix(char *s, int i, int flag)
{
    char *str;
    int j;

    str = NULL;
    j = i;
    if (!flag)
    {
        while (j >= 0 && !isspace(s[j]))
            j--;
        if (j + 1 != i)
            str = ft_strndup(&s[j + 1], i);
    }
    else
    {
        while (s[j] && !isspace(s[j]))
            j++;
        if (j > 1)
            str = ft_strndup(&s[i + 1], j);
    }
    return (str);
}

int    empty_space(char *s, int idx)
{
    int i;

    i = idx;
    while (i >= 0 && !isspace(s[i]))
        s[i--] = 0;
    return (i + 1);
}

void    add_first_filename(t_expand *params, char *match, int match_len)
{
    char    *tmp;

    params->res_idx = empty_space(params->res, params->res_idx - 1);
    if (params->res)
        ft_strlcat(&params->res[params->res_idx], match, params->res_size + 1);
    if (match_len > params->res_size)
    {
        tmp = ft_strjoin(params->res, &match[params->res_size]);
        free(params->res);
        params->res = tmp;
        params->res_idx += match_len;
        params->res_size = match_len;
    }
}

void    add_match(t_expand *params, char *match, int match_len, bool *flag)
{
    char    *tmp;
    char    *tmp2;

    if (!*flag)
    {
        add_first_filename(params, match, match_len);
        *flag = true;
    }
    else
    {
        tmp = ft_strjoin(params->res, " ");
        tmp2 = ft_strjoin(tmp, match);
        free(params->res);
        free(tmp);
        params->res = tmp2;
        params->res_idx += match_len + 1;
        params->res_size += match_len + 1;
    }
}

void   fetsh_files(t_expand *params, char *prefix, char *suffix)
{
    DIR *dir;
    struct dirent *entry;
    size_t  name_len;
    bool    flag;

    dir = opendir(".");
    if (!dir)
        return;
    flag = false;
    while ((entry = readdir(dir)))
    {
        name_len = ft_strlen(entry->d_name);
        if (!prefix && !suffix)
            add_match(params, entry->d_name, name_len, &flag);
        else if (prefix && !strncmp(entry->d_name, prefix, ft_strlen(prefix)))
        {
            if (suffix && !strncmp(&entry->d_name[name_len - ft_strlen(suffix)], suffix, ft_strlen(suffix)))
                add_match(params, entry->d_name, name_len, &flag);
        }
        else if (!prefix)
        {
            if (suffix && !strncmp(&entry->d_name[name_len - ft_strlen(suffix)], suffix, ft_strlen(suffix)))
                add_match(params, entry->d_name, name_len, &flag);
        }
    }
    closedir(dir);
}

void expand_wildcards(t_expand *params)
{
    char *prefix;
    char *suffix;

    prefix = get_prefix_suffix(params->str, params->i, 0);
    suffix = get_prefix_suffix(params->str, params->i, 1);
    fetsh_files(params, prefix, suffix);
    if (suffix)
        params->i += ft_strlen(suffix) +1;
    else
        params->i++;
    free(prefix);
    free(suffix);
    return;
}
