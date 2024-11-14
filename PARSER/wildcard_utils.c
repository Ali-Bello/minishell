/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:22:30 by marvin            #+#    #+#             */
/*   Updated: 2024/11/13 19:59:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	replace_string(t_expand *params, char *match, int match_len)
{
	free(params->res);
	params->res = ft_strdup(match);
	params->res_idx += match_len;
	params->res_size = match_len;
}

void	add_match(t_expand *params, t_wildcard *specs)
{
	char	*tmp;
	char	*tmp2;

	if (specs->flags[2] || (!specs->flags[2] && specs->flags[1]))
	{
		tmp = ft_strtrim(specs->current_dir, "./");
		tmp2 = ft_strjoin(tmp, "/");
		free(tmp);
		tmp = ft_strjoin(tmp2, specs->entry->d_name);
		free(tmp2);		
	}
	else if (specs->flags[2])
		tmp = ft_strjoin(specs->entry->d_name, "/");
	else
		tmp = ft_strdup(specs->entry->d_name);
	if (!specs->flags[4])
	{
		replace_string(params, tmp, specs->name_len);
		specs->flags[4] = true;
		while (params->str[params->i] && !ft_isspace(params->str[params->i]))
			params->i++;
	}
	else
		add_node(&specs->node, new_node(ft_strdup(tmp), WORD));
	free(tmp);
}
