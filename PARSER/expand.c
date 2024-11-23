/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 03:36:24 by marvin            #+#    #+#             */
/*   Updated: 2024/11/18 18:09:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_varname(char *s, int *j)
{
	int	i;

	i = 0;
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	*j += i + 1;
	return (ft_substr(s, 0, i));
}

void	expand_exit_status(t_expand *params)
{
	char	*value;

	value = ft_itoa(EXIT_STATUS);
	params->res = append_value(params, value);
	if (!params->res)
		return ;
	free(value);
	params->i += 2;
}

void	expand_var(t_expand *params, t_list *node)
{
	char	*var_name;
	char	*value;

	if (params->quotes_flags[1] || !params->str[params->i + 1])
	{
		params->res = extend_string(params);
		params->i++;
		return ;
	}
	if (params->str[params->i + 1] == '?')
	{
		expand_exit_status(params);
		return ;
	}
	var_name = get_varname(&params->str[params->i + 1], &params->i);
	value = getenv(var_name);
	if (!params->quotes_flags[0] && value)
		append_words(node, params, value);
	else if (value)
		params->res = append_value(params, value);
	else
		params->res = append_value(params, "");
	free(var_name);
}

void	set_quotes_flags(t_expand *params)
{
	if (params->str[params->i] == '\'' && !params->quotes_flags[0])
	{
		params->quotes_flags[1] = !params->quotes_flags[1];
		if (params->i > 0 && params->str[params->i - 1] == '\'')
			params->res = append_value(params, "");
	}
	else if (params->str[params->i] == '\'')
		params->res = extend_string(params);
	if (params->str[params->i] == '"' && !params->quotes_flags[1])
	{
		params->quotes_flags[0] = !params->quotes_flags[0];
		if (params->i > 0 && params->str[params->i - 1] == '"')
			params->res = append_value(params, "");
	}
	else if (params->str[params->i] == '"')
		params->res = extend_string(params);
	params->i++;
}

void	expand_rm_quotes(t_list *node, char *s)
{
	t_expand	params;

	if (node->expand_flag)
		return ;
	ft_bzero(&params, sizeof(t_expand));
	params.str = s;
	while (s && s[params.i])
	{
		if (s[params.i] != '\'' && s[params.i] != '"' && s[params.i] != '$'
			&& s[params.i] != '*')
		{
			params.res = extend_string(&params);
			params.i++;
		}
		else if (s[params.i] == '\'' || s[params.i] == '"')
			set_quotes_flags(&params);
		else if (s[params.i] == '$')
			expand_var(&params, node);
		else if (s[params.i] == '*')
			expand_wildcards(&params, node);
	}
	free(s);
	node->s = params.res;
	if (params.to_sort)
		sort_fnames(node, params.idx_node->next);
}
