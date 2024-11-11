/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:22:30 by marvin            #+#    #+#             */
/*   Updated: 2024/11/11 18:43:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_first_filename(t_expand *params, char *match, int match_len)
{
	char	*tmp;

	tmp = ft_strjoin(params->res, match);
	free(params->res);
	params->res = tmp;
	params->res_idx += match_len;
	params->res_size = match_len;
}

void	add_match(t_expand *params, t_wildcard *specs)
{
	if (!specs->flag)
	{
		add_first_filename(params, specs->entry->d_name, specs->name_len);
		specs->flag = true;
		params->i += ft_strlen(specs->node->s);
	}
	else
		add_node(&specs->node, new_node(ft_strdup(specs->entry->d_name), WORD));
}
