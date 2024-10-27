/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:22:30 by marvin            #+#    #+#             */
/*   Updated: 2024/10/15 12:22:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	empty_space(char *s, int idx)
{
	int	i;

	i = idx;
	while (i >= 0 && !ft_isspace(s[i]))
		s[i--] = 0;
	return (i + 1);
}

void	add_first_filename(t_expand *params, char *match, int match_len)
{
	char	*tmp;

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

void	add_match(t_expand *params, t_wildcard *specs)
{
	char	*tmp;
	char	*tmp2;

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
