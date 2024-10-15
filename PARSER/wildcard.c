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

#include "../includes/minishell.h"

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

void    add_match(t_expand *params, t_wildcard *specs)
{
    char    *tmp;
    char    *tmp2;

    if (!specs->flag)
    {
        add_first_filename(params, specs->entry->d_name, specs->name_len);
        specs->flag = true;
    }
    else
    {
        tmp = ft_strjoin(params->res, " ");
        tmp2 = ft_strjoin(tmp, specs->entry->d_name);
        free(params->res);
        free(tmp);
        params->res = tmp2;
        params->res_idx += specs->name_len + 1;
        params->res_size += specs->name_len + 1;
    }
}

bool    match_wildcards(char *filename, char **fragments)
{
    int i;
    char *pos;

    i = 0;
    pos = filename;
    while (fragments[i])
    {
        pos = strstr(pos, fragments[i]);
        if (!pos) 
            return false;
        pos += ft_strlen(fragments[i]);
        i++;
    }
    return true;
}

bool    match_simple_wildcard(char *filename, char *pattern, size_t name_len)
{
    size_t pattern_len;
    
    pattern_len = ft_strlen(pattern);
    if (!strcmp(pattern, "*"))
        return true;
    if (pattern[0] == '*' && pattern[pattern_len - 1] == '*')
        return (strstr(filename, pattern + 1) != NULL);
    else if (pattern[0] == '*')
        return (name_len >= pattern_len - 1 &&
                !strcmp(&filename[name_len - (pattern_len - 1)], pattern + 1));
    else if (pattern[pattern_len - 1] == '*')
        return !strncmp(filename, pattern, pattern_len - 1);
    return false;
}
void    match_patterns(t_expand *params, t_wildcard *specs)
{
    specs->fragments = ft_split(specs->pattern, '*');
    while ((specs->entry = readdir(specs->dir)))
    {
        specs->name_len = ft_strlen(specs->entry->d_name);
        // Handle simple cases like '*something*' or 'something*'
        if (match_simple_wildcard(specs->entry->d_name, specs->pattern, specs->name_len))
            add_match(params, specs);
        // If pattern has fragments from '*', match multiple wildcards
        else if (match_wildcards(specs->entry->d_name, specs->fragments))
            add_match(params, specs);
    }
}

void   fetsh_files(t_expand *params, t_wildcard *specs)
{
    specs->dir = opendir(".");
    if (!specs->dir)
        return;
    specs->flag = false;
    if (!specs->pattern)
    {
        while ((specs->entry = readdir(specs->dir)))
        {
            specs->name_len = ft_strlen(specs->entry->d_name);
            add_match(params, specs);
        }
    }
    else
        match_patterns(params, specs);
    closedir(specs->dir);
    free(specs->fragments);
}

char    *get_pattern(char *str, int idx)
{
    int i;
    int len;
    char *s;

    i = idx;
    s = NULL;
    while (i >= 0 && !isspace(str[i]))
        i--;
    len = idx;
    while (str[len] && !isspace(str[len]))
        len++;
    if (i > 1 || len > 1)
        s = ft_substr(str, i + 1, len);
    return (s);
}

void expand_wildcards(t_expand *params)
{
    t_wildcard  specs;

    specs.pattern = get_pattern(params->str, params->i);
    specs.name_len = 0;
    fetsh_files(params, &specs);
    if (specs.flag)
    {
        while(params->str[params->i] && !isspace(params->str[params->i]))
            params->i++;
    }
    else
    {
        params->res = extend_string(params);
        params->i++;
    }
    free(specs.pattern);
    return;
}
