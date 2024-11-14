/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 04:05:37 by marvin            #+#    #+#             */
/*   Updated: 2024/11/13 19:59:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_pattern(char *str, int idx)
{
	int		i;
	int		len;
	char	*s;

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

bool	match_found(t_wildcard *specs)
{
	int		i;
	char	*pos;
	size_t	len;

	i = 0;
	pos = specs->entry->d_name;
	while (specs->fragments && specs->fragments[i])
	{
		len = ft_strlen(specs->fragments[i]);
		if (i == 0 && !specs->flags[0])
			pos = ft_strnstr(pos, specs->fragments[i], len);
		else if (specs->flags[3])
		{
			if (ft_strncmp(specs->entry->d_name, specs->fragments[i], len))
				pos = NULL;
			else
				pos = specs->entry->d_name;
		}
		else if (!specs->fragments[i + 1] && !specs->flags[1])
			pos = ft_strnstr(&specs->entry->d_name[ft_strlen(specs->entry->d_name)
					- len], specs->fragments[i], len);
		else
			pos = ft_strnstr(pos, specs->fragments[i], ft_strlen(pos));
		if (!pos)
			return (false);
		pos += ft_strlen(specs->fragments[i++]);
	}
	return (true);
}

void	dir_match(t_expand *params, t_wildcard *specs)
{
	t_wildcard	tmp;

	if (specs->fragments[0][0] == '/' && !specs->fragments[0][1]
		&& !specs->flags[1])
		return ((void)add_match(params, specs));
	tmp.current_dir = ft_strjoin(specs->current_dir, specs->entry->d_name);
	tmp.pattern = specs->pattern;
	tmp.node = specs->node;
	for (int i = 0; i < 5; i++)
		tmp.flags[i] = specs->flags[i];
	tmp.flags[2] = false;
	tmp.fragments = ft_split(specs->pattern, '*');
	if (specs->fragments[0][0] == '/' && specs->fragments[0][1])
	{
		char *new = ft_strdup(&tmp.fragments[0][1]);
		free(tmp.fragments[0]);
		tmp.fragments[0] = new;
		tmp.flags[3] = true;
	}
	else
		tmp.fragments = &specs->fragments[1];
	tmp.dir = opendir(tmp.current_dir);
	match_patterns(params, &tmp);
	specs->flags[4] = tmp.flags[4];
	free(tmp.current_dir);
	free_array(tmp.fragments);
	closedir(tmp.dir);
}

void	match_patterns(t_expand *params, t_wildcard *specs)
{
	specs->entry = readdir(specs->dir);
	while (specs->entry)
	{
		if (specs->entry->d_name[0] == '.' && specs->fragments && specs->fragments[0][0] != '.')
		{
			specs->entry = readdir(specs->dir);
			continue ;
		}
		specs->name_len = ft_strlen(specs->entry->d_name);
		if (specs->entry->d_type == DT_DIR && specs->flags[2])
			dir_match(params, specs);
		else if (match_found(specs))
			add_match(params, specs);
		specs->entry = readdir(specs->dir);
	}
}

void	fetsh_files(t_expand *params, t_wildcard *specs)
{
	specs->current_dir = "./";
	specs->fragments = ft_split(specs->pattern, '*');
	if (specs->fragments && specs->pattern[0] == '*')
		specs->flags[0] = true;
	if (specs->fragments && specs->pattern[ft_strlen(specs->pattern)
		- 1] == '*')
		specs->flags[1] = true;
	if (specs->flags[0] && ft_strchr(specs->pattern, '/'))
		specs->flags[2] = true;
	specs->dir = opendir(specs->current_dir);
	if (!specs->dir)
		return ;
	match_patterns(params, specs);
	closedir(specs->dir);
}

void	expand_wildcards(t_expand *params, t_list *node)
{
	t_wildcard	specs;

	ft_memset(&specs, 0, sizeof(t_wildcard));
	specs.node = node;
	if (params->quotes_flags[0] || params->quotes_flags[1])
	{
		params->res = extend_string(params);
		params->i++;
		return ;
	}
	specs.pattern = get_pattern(params->str, params->i);
	fetsh_files(params, &specs);
	free(specs.pattern);
	free_array(specs.fragments);
	if (!specs.flags[4])
	{
		params->res = extend_string(params);
		params->i++;
	}
	return ;
}
