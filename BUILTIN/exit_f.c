/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamella <anamella@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 22:44:52 by anamella          #+#    #+#             */
/*   Updated: 2024/11/22 22:50:10 by anamella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	check_arg(char *s)
{
	static int	i;
	static int	num;
	static int	space;
	static int	sign;

	while (s[i])
	{
		if (s[i] == '-' || s[i] == '+')
		{
			if (num)
				return (0);
			sign++;
		}
		if (!ft_isdigit(s[i]) && !ft_isspace(s[i]) && s[i] != '-'
			&& s[i] != '+')
			return (1);
		if (ft_isdigit(s[i]))
			num = 1;
		if (ft_isspace(s[i]) && num)
			space = 1;
		if ((space && ft_isdigit(s[i])) || sign > 1)
			return (1);
		i++;
	}
	return (0);
}

int	get_exit(char *s)
{
	if (check_arg(s))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
	else
		exit(ft_atoi(s));
	return (0);
}

int	exit_f(char **args, t_mini *mini)
{
	int	count;
	int	status;

	count = count_args(args);
	printf("%s\n", "exit");
	if (count > 1)
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	else
	{
		if (count == 0)
		{
			printf("in exit == %d\n", mini->exit);
			exit(mini->exit);
			printf("in exit == %d\n", mini->exit);
		}
		else
		{
			status = get_exit(args[0]);
			exit(status);
		}
	}
}
