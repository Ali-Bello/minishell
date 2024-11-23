/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_f.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamella <anamella@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 22:44:57 by anamella          #+#    #+#             */
/*   Updated: 2024/11/22 22:44:58 by anamella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	export_f(char **env, t_mini *mini)
{
	int		i;
	int		status;
	int		exit;
	t_env	**env_l;

	i = 0;
	status = 0;
	env_l = &mini->env;
	if (!env || !*env)
		return (env_f(*env_l, 1), 0);
	exit = 0;
	while (env && env[i])
	{
		if (get_env(get_var(env[i], &status), *env_l))
			set_env(get_var(env[i], &status), get_val(env[i], &status), env_l);
		else
			add_env(env_l, new_env(env[i], &status));
		i++;
		if (status == 1)
			exit = 1;
		status = 0;
	}
	return (exit);
}
