/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_f.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 22:44:40 by anamella          #+#    #+#             */
/*   Updated: 2024/11/30 01:06:59 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env_f(t_env *env, int flag)
{
	char	*val;

	while (env)
	{
		if (flag == 1)
		{
			val = env->val;
			if (val)
				printf("declare -x %s=\"%s\"\n", env->var, env->val);
			else
				printf("declare -x %s\n", env->var);
		}
		else if (env->var && env->val)
			printf("%s=%s\n", env->var, env->val);
		env = env->next;
	}
	return (0);
}
