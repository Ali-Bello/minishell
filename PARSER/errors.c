/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 05:05:39 by marvin            #+#    #+#             */
/*   Updated: 2024/11/26 21:06:01 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_parenthesis(char *input, int i, bool *valid)
{
	int	j;

	if (input[i] == '(' && *valid == true)
	{
		*valid = false;
		j = i + 1;
		while (input[j] && ft_isspace(input[j]))
			j++;
		if (!input[j])
			printf("syntax_error near unexpected token `('\n");
		else if (input[j] == '&' && input[j + 1] && input[j + 1] == '&')
			printf("syntax_error near unexpected token `&&'\n");
		else if (input[j] == '&' && (!input[j + 1] || input[j + 1] != '&'))
			printf("syntax_error near unexpected token `&'\n");
		else if (input[j] == '|' && input[j + 1] && input[j + 1] == '|')
			printf("syntax_error near unexpected token `||'\n");
		else if (input[j] == '|' && (!input[j + 1] || input[j + 1] != '|'))
			printf("syntax_error near unexpected token `|'\n");
		else if (input[j] == ')')
			printf("syntax_error near unexpected token `)'\n");
		else if (input[j] == ';')
			printf("syntax_error near unexpected token `;'\n");
		else
			*valid = true;
	}
}

bool	syntax_check(char *input)
{
	int		i;
	bool	valid;

	i = 0;
	valid = true;
	if (input && (*input == ')' || *input == ';'))
		return (printf("syntax_error near unexpected token `%c'\n", *input),
			false);
	else if (input && *input == '&' && input[1] == '&')
		return (printf("syntax_error near unexpected token `%c%c'\n", *input,
				*input), false);
	else if (input && *input == '&' && input[1] != '&')
		return (printf("syntax_error near unexpected token `%c'\n", *input),
			false);
	while (input && input[i] && valid)
	{
		check_parenthesis(input, i, &valid);
		check_pipes(input, i, &valid);
		check_repeating_operators(input, i, '|', &valid);
		check_repeating_operators(input, i, '<', &valid);
		check_repeating_operators(input, i, '>', &valid);
		i++;
	}
	return (valid);
}
