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

char    *get_pattern(char *str, int idx)
{
    int i;
    int len;
    char *s;

    i = idx;
    s = NULL;
    while (i >= 0 && !ft_isspace(str[i]))
        i--;
    len = idx;
    while (str[len] && !ft_isspace(str[len]))
        len++;
    if (i > 1 || len > 1)
        s = ft_substr(str, i + 1, len);
    return (s);
}

bool    match_found(char *filename, char **fragments)
{
    int i;
    char *pos;

    i = 0;
    pos = filename;
    while (fragments[i])
    {
        if (i == 0)
            pos = ft_strnstr(pos, fragments[i], ft_strlen(fragments[0]));
        else if (!fragments[i + 1])
            pos = ft_strnstr(&filename[ft_strlen(filename) - \
            ft_strlen(fragments[i])], fragments[i], ft_strlen(fragments[i]));
        else
            pos = ft_strnstr(pos, fragments[i], ft_strlen(pos));
        if (!pos)
            return false;
        pos += ft_strlen(fragments[i]);
        i++;
    }
    return true;
}

void    match_patterns(t_expand *params, t_wildcard *specs)
{
    while ((specs->entry = readdir(specs->dir)))
    {
        if (specs->entry->d_name[0] == '.')
            continue;
        specs->name_len = ft_strlen(specs->entry->d_name);
        if (!specs->fragments)
            add_match(params, specs);
        else if (match_found(specs->entry->d_name, specs->fragments))
            add_match(params, specs);
    }
}

void   fetsh_files(t_expand *params, t_wildcard *specs)
{
    char *dir_name;
    char  *tmp;

    specs->current_dir = "./";
    dir_name = NULL;
    specs->fragments = ft_split(specs->pattern, '*');
    if (specs->fragments && (tmp = ft_strrchr(specs->fragments[0], '/')))
    {
        dir_name = ft_substr(specs->fragments[0], 0, \
        tmp - specs->fragments[0]);
        tmp = ft_strdup(tmp + 1);
        free(specs->fragments[0]);
        specs->fragments[0] = tmp;
    }
    specs->current_dir = ft_strjoin(specs->current_dir, dir_name);
    specs->dir = opendir(specs->current_dir);
    if (!specs->dir)
        return;
    match_patterns(params, specs);
    closedir(specs->dir);
    free(dir_name);
    return ;
}

void expand_wildcards(t_expand *params, int squotes, int dquotes)
{
    t_wildcard  specs;

    ft_memset(&specs, 0, sizeof(t_wildcard));
    if (squotes || dquotes)
    {
        params->res = extend_string(params);
        params->i++;
        return;
    }
    specs.pattern = get_pattern(params->str, params->i);
    fetsh_files(params, &specs);
    if (specs.flag)
    {
        while(params->str[params->i] && !ft_isspace(params->str[params->i]))
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
