/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 03:36:24 by marvin            #+#    #+#             */
/*   Updated: 2024/10/13 06:18:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../LEXER/lexer.h"

char    *get_varname(char *s, int *j)
{
    int i;

    i = 0;
    while (s[i] && !isspace(s[i]) && (isalnum(s[i]) || s[i] == '_'))
        i++;
    *j += i;
    return (ft_strndup(s, i));
}

void    expand_exit_status(t_expand *params)
{
    char    *value;
    size_t   value_len;

    // value = ft_itoa(EXIT_STATUS);
    value_len = strlen(value);
    params->res = realloc(params->res, params->res_size + value_len + 1);
    if (!params->res)
        return;
    strcpy(params->res + params->res_idx, value);
    params->res_idx += value_len;
    free(value);
    params->i++; // Skip the '?' character
}

void    expand_var(t_expand *params)
{
    char *var_name;
    char *value;
    size_t value_len;

        //Special case for '$?'
    // if (params->str[params->i + 1] == '?')
    // {
    //     expand_exit_status(params);
    //     return;
    // }
    var_name = get_varname(&params->str[params->i + 1], &params->i); // Update *i to point to the end of var name
    value = getenv(var_name);
    value_len = (value != NULL) * strlen(value) + (value == NULL) * 0;
    // Expand the result buffer
    // printf("-->[%d]\n", params->res_size);
    params->res = realloc(params->res, params->res_size + value_len + 1);
    if (!params->res) 
        return (free(var_name));// Handle allocation failure
    
    strcpy(params->res + params->res_idx, value);
    params->res_idx += value_len;
    free(var_name);
    params->i++;
}

void    set_quotes_flags(char c, int flags[], int *i)
{
    if (c == '\'' && !flags[0])
        flags[1] = !flags[1];
    if (c == '\"' && !flags[1])
        flags[0] = !flags[0];
    (*i)++;
}

char    *extend_string(t_expand *params)
{
    char *str;

    str = malloc(params->res_size + 2);
    if (!str)
        return NULL;
    if (params->res)
        strcpy(str, params->res);
    str[params->res_idx++] = params->str[params->i];
    str[params->res_idx] = '\0';
    params->res_size++;
    free(params->res);
    return (str);
}

char *expand_and_remove_quotes(char *s)
{
    t_expand params;
    int quotes_flags[2];

    memset(&params, 0, sizeof(t_expand));
    memset(&quotes_flags, 0, sizeof(quotes_flags));
    params.str = s;
    while (s[params.i])
    {
        if (s[params.i] == '\'' || s[params.i] == '"')
        {
            set_quotes_flags(s[params.i], quotes_flags, &params.i);
            continue;
        }
        if (s[params.i] == '$' && !quotes_flags[1])
        {
            expand_var(&params);
            continue;
        }
        params.res = extend_string(&params);
        if (!params.res)
            return NULL;
        params.i++;
    }
    free(s);
    return (params.res);
}
