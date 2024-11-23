/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamella <anamella@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 22:45:50 by anamella          #+#    #+#             */
/*   Updated: 2024/11/23 01:56:05 by anamella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirections_type(t_redir *redirections, t_mini *mini)
{
	int	fd;

	(void)mini;
	fd = -1;
	if (redirections->mode == APPEND)
		fd = open(redirections->file, O_CREAT | O_RDWR | O_APPEND, 0644);
	else if (redirections->mode == REDIROUT)
		fd = open(redirections->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (redirections->mode == REDIRIN)
		fd = open(redirections->file, O_RDONLY);
	else if (redirections->mode == HEREDOC)
		fd = redirections->fd;
	return (fd);
}

int	check_redirection(t_tree *root, t_mini *mini)
{
	int		fd;
	t_redir	*redirections;

	redirections = root->data.redirections;
	if (redirections)
	{
		while (redirections)
		{
			fd = redirections_type(redirections, mini);
			if (fd == -1)
			{
				perror(redirections->file);
				return (1);
			}
			if (redirections->mode == APPEND || redirections->mode == REDIROUT)
				dup2(fd, 1);
			else if (redirections->mode == REDIRIN
				|| redirections->mode == HEREDOC)
				dup2(fd, 0);
			close(fd);
			redirections = redirections->next;
		}
	}
	return (0);
}

int	count_env(t_env *tmp)
{
	int	count;

	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

char	**create_char_env(t_env *env)
{
	int		i;
	int		count;
	char	**ev;
	char	*c_tmp;
	t_env	*tmp;

	count = count_env(env);
	if (count == 0)
		return (NULL);
	ev = (char **)malloc(sizeof(char *) * (count + 1));
	if (!ev)
		return (perror("malloc"), NULL);
	tmp = env;
	i = 0;
	while (tmp)
	{
		ev[i] = ft_strjoin(tmp->var, "=");
		c_tmp = ev[i];
		ev[i] = ft_strjoin(c_tmp, tmp->val);
		free(c_tmp);
		i++;
		tmp = tmp->next;
	}
	return (ev[i] = NULL, ev);
}
