/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamella <anamella@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 22:45:08 by anamella          #+#    #+#             */
/*   Updated: 2024/11/22 22:48:03 by anamella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	unset_f(char **env, t_mini *mini)
{
	int		i;
	t_env	**env_l;

	i = 0;
	env_l = &mini->env;
	while (env && env[i])
	{
		del_env(env_l, env[i]);
		i++;
	}
	return (0);
}
