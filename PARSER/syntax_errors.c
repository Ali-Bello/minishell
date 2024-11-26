/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 23:29:53 by aderraj           #+#    #+#             */
/*   Updated: 2024/11/26 21:50:28 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	amibigous_redirect(char *input, int j)
{
	char	*tmp;
	int		x;

	x = j;
	while (input[x] && !ft_isspace(input[x]))
		x++;
	tmp = ft_substr(input, j, x - j);
	printf("[%s] ambigious redirect \n", tmp);
	free(tmp);
}

void	operators_check(char *input, char c, int j)
{
	if (input[j] == '*')
		amibigous_redirect(input, j);
	else if ((c == 60 && input[j] == 62) || (c == 62 && input[j] == 60))
		printf("syntax_error near unexpected token `%c'\n", input[j]);
	else if (input[j])
	{
		if (input[j] == c && input[j + 1] && input[j + 1] == c)
			printf("syntax_error near unexpected token `%c%c'\n", c, c);
		else if (input[j] == c && (!input[j + 1] || input[j + 1] != c))
			printf("syntax_error near unexpected token `%c'\n", c);
		else if (input[j] == '|' && input[j + 1] && input[j + 1] == '|')
			printf("syntax_error near unexpected token `||'\n");
		else if (input[j] == '|' && (!input[j + 1] || input[j + 1] != '|'))
			printf("syntax_error near unexpected token `|'\n");
		else if (input[j + 1] == '&' && input[j + 1] && input[j + 1] == '&')
			printf("syntax_error near unexpected token `&&'\n");
		else if (input[j] == '&' && (!input[j + 1] || input[j + 1] != '&'))
			printf("syntax_error near unexpected token `&'\n");
		else if (input[j] == '(' || input[j] == ')')
			printf("syntax_error near unexpected token `%c'\n", input[j]);
		else if (input[j] == ';')
			printf("syntax_error near unexpected token `;'\n");
	}
}

void	check_repeating_operators(char *input, int i, char c, bool *valid)
{
	int		j;

	if (*valid == false)
		return ;
	j = i;
	while (input[j] && input[j] == c)
		j++;
	if (j >= i + 1)
	{
		if (j == i + 1 || j == i + 2)
		{
			while (ft_isspace(input[j]))
				j++;
			if (!input[j])
				printf("syntax_error near unexpected token `newline'\n");
			else
				operators_check(input, c, j);
		}
		else if ((j + i) % 2 && j + i <= 4)
			printf("syntax_error near unexpected token `%c'\n", c);
		else if ((j + i) % 2 == 0)
			printf("syntax_error near unexpected token `%c%c'\n", c, c);
		if (!ft_isalnum(input[j]) && (is_operator(input[j]) || input[j] == '*'))
			*valid = false;
	}
}

void	check_surrondings(char *input, int i, bool *valid, int flag)
{
	int	j;
	int	loop_condition;
	int	checks_condition;

	j = i;
	loop_condition = (j >= 0) * (flag == -1) + (input[j] != 0) * (flag == 1);
	checks_condition = (j > 0) * (flag == -1) + (input[j] != 0) * (flag == 1);
	if (flag == -1)
		while (j >= 0 && ft_isspace(input[j]))
			j--;
	else
		while (loop_condition && ft_isspace(input[j]))
			j += flag;
	if (checks_condition && input[j] == '&' && input[j + flag] == '&')
		printf("syntax_error near unexpected token `&&'\n");
	else if (checks_condition && input[j] == '|' && input[j + flag] == '|')
		printf("syntax_error near unexpected token `||'\n");
	else if (checks_condition && input[j] == '&' && input[j + flag] != '&')
		printf("syntax_error near unexpected token `&'\n");
	else
		*valid = true;
}

void	check_pipes(char *input, int i, bool *valid)
{
	if (input[i] == '|' && *valid == true)
	{
		*valid = false;
		if (i == 0 && input[i] == '|' && (!input[i + 1] || input[i + 1] != '|'))
			printf("syntax_error near unexpected token `|'\n");
		else if (i == 0 && input[i] == '|' && input[i + 1] && input[i
				+ 1] == '|')
			printf("syntax_error near unexpected token `||'\n");
		else
		{
			check_surrondings(input, i - 1, valid, -1);
			*valid = false;
			check_surrondings(input, i + 1, valid, 1);
		}
	}
}
