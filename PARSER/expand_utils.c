/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 07:21:23 by marvin            #+#    #+#             */
/*   Updated: 2024/10/27 03:38:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_args_count(t_list *list)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = list;
	while (tmp && tmp->type == WORD)
	{
		if (tmp->s)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

char	*extend_string(t_expand *params)
{
	char	*str;

	str = malloc(params->res_size + 2);
	if (!str)
		return (NULL);
	if (params->res)
		ft_strlcpy(str, params->res, params->res_size + 2);
	str[params->res_idx++] = params->str[params->i];
	str[params->res_idx] = '\0';
	params->res_size++;
	free(params->res);
	return (str);
}

char	*append_value(t_expand *params, char *value)
{
	size_t	value_len;
	char	*str;

	if (!value)
		value = "";
	value_len = ft_strlen(value);
	str = malloc(params->res_size + value_len + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, params->res, params->res_size + 1);
	ft_strlcat(str, value, params->res_size + value_len + 2);
	params->res_idx += value_len;
	params->res_size += value_len;
	free(params->res);
	return (str);
}

void	append_words(t_list *node, t_expand *params, char *value)
{
	t_list	*tmp;
	char	**s;
	int		i;

	if (node->amibiguous_redir)
	{
		params->res = append_value(params, value);
		return ;
	}
	s = ft_split(value, ' ');
	if (s && *s)
		params->res = append_value(params, *s);
	i = 1;
	while (s && s[i])
	{
		tmp = node->next;
		node->next = new_node(s[i], WORD);
		if (ft_strchr(s[i], '\'') || ft_strchr(s[i], '"'))
			node->next->expand_flag = 1;
		node->next->next = tmp;
		node = node->next;
		i++;
	}
	free(*s);
	free(s);
}

char	**extend_array(char **arr, char *new, int i, int size)
{
	char	**new_arr;

	new_arr = arr;
	if (i >= size)
	{
		new_arr = malloc(sizeof(char *) * size + 2);
		if (!new_arr)
			return (NULL);
		new_arr[i + 1] = NULL;
		i = 0;
		while (i < size)
		{
			new_arr[i] = arr[i];
			i++;
		}
		new_arr[i] = ft_strdup(new);
		free(arr);
	}
	else
		new_arr[i] = ft_strdup(new);
	return (new_arr);
}
