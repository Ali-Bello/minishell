/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 03:36:24 by marvin            #+#    #+#             */
/*   Updated: 2024/10/23 06:36:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    *get_varname(char *s, int *j)
{
    int i;

    i = 0;
    while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
        i++;
    *j += i + 1;
    return (ft_substr(s, 0, i));
}

void    expand_exit_status(t_expand *params)
{
    char    *value;

    value = ft_itoa(EXIT_STATUS);
    params->res = append_value(params, value);
    if (!params->res)
        return;
    free(value);
    params->i += 2;
}

void    expand_var(t_expand *params, int flags[], t_list *node)
{
    char *var_name;
    char *value;


    if (flags[1] || !params->str[params->i + 1])
    {
        params->res = extend_string(params);
        params->i++;
        return;
    }
    if (params->str[params->i + 1] == '?')
    {
        expand_exit_status(params);
        return;
    }
    var_name = get_varname(&params->str[params->i + 1], &params->i);
    value = getenv(var_name);
    if (!flags[0])
        append_words(node, params, value);
    else 
        params->res = append_value(params, value);
    if (!params->res)
        return (free(var_name));
    free(var_name);
}

void    set_quotes_flags(t_expand *params, int flags[])
{
    if (params->str[params->i] == '\'' && !flags[0])
    {
        flags[1] = !flags[1];
        if (params->i > 0 && params->str[params->i - 1] == '\'')
            params->res = append_value(params, "");
    }
    else if (params->str[params->i] == '\'')
        params->res = extend_string(params);
    if (params->str[params->i] == '"' && !flags[1])
    {
        flags[0] = !flags[0];
        if (params->i > 0 && params->str[params->i - 1] == '"')
            params->res = append_value(params, "");
    }
    else if (params->str[params->i] == '"')
        params->res = extend_string(params);
    params->i++;
}

char *expand_rm_quotes(t_list *node, char *s)
{
    t_expand params;
    int quotes_flags[2];

    ft_bzero(&params, sizeof(t_expand));
    ft_bzero(&quotes_flags, sizeof(quotes_flags));
    params.str = s;
    while (s[params.i])
    {
        if (s[params.i] != '\'' && s[params.i] != '"'\
        && s[params.i] != '$' && s[params.i] != '*')
        {
            params.res = extend_string(&params);
            if (!params.res)
                return NULL;
            params.i++;
        }
        else if (s[params.i] == '\'' || s[params.i] == '"')
            set_quotes_flags(&params, quotes_flags);
        else if (s[params.i] == '$')
            expand_var(&params, quotes_flags, node);
        else if (s[params.i] == '*')
            expand_wildcards(&params, quotes_flags[1], quotes_flags[0]);
    }
    free(s);
    return (params.res);
}
