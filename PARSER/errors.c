/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 05:05:39 by marvin            #+#    #+#             */
/*   Updated: 2024/11/29 16:00:30 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	check_ambiguous_redirect(t_list *list)
{
	t_redir	*tmp;

	while (list)
	{
		tmp = list->data.redirections;
		while (tmp)
		{
			if (tmp->ambiguous)
			{
				ft_putstr_fd(tmp->file, 2);
				ft_putstr_fd(": ambiguous redirect\n", 2);
				return (true);
			}
			tmp = tmp->next;
		}
		list = list->next;
	}
	return (false);
}

bool	quotes_parenthesis_errors(char *input, int i)
{
	bool	single_quote_flag;
	bool	double_quote_flag;
	int		parenthesis_count;

	single_quote_flag = false;
	double_quote_flag = false;
	parenthesis_count = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !double_quote_flag)
			single_quote_flag = !single_quote_flag;
		else if (input[i] == '"' && !single_quote_flag)
			double_quote_flag = !double_quote_flag;
		else if (input[i] == '(' && !single_quote_flag && !double_quote_flag)
			parenthesis_count++;
		else if (input[i] == ')' && !single_quote_flag && !double_quote_flag)
			parenthesis_count--;
		i++;
	}
	if (single_quote_flag || double_quote_flag)
		return (report_error(NULL, -1), true);
	if (parenthesis_count > 0)
		return (report_error(NULL, -2), true);
	return (false);
}
