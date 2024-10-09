/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_prime.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 03:13:26 by marvin            #+#    #+#             */
/*   Updated: 2024/10/09 05:38:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_info info;

int is_operator(char c)
{
    return ((c == '|' || c == '>' || c == '<'));
}

void    parse_words(char *s, int *i)
{
    int j;

    if (!s)
        return;
    j = 0;
    while (s[j] && !is_operator(s[j]) && !isspace(s[j])
        &&  s[j] != '"' && s[j] != '\'')
        j++;
    add_node(&info.node, new_node(ft_strndup(s, j), *i, 6));
    *i += j;
}

void    parse_quotes(char *s, int *i)
{
    int     j;
    char    delim;

    j = 1;
    delim = '\'' * (s[0] == '\'') + '"' * (s[0] == '"');
    while (s[j] && s[j] != delim)
        j++;
    printf("j = %d\n", j);
    delim = SINGLEQUOTEDWORD * (delim == '\'') + DOUBLEQUOTEDWORD * (delim == '"');
    add_node(&info.node, new_node(ft_strndup(s, j + 1), *i, delim));
    *i += j;
}

void    parse_operators(char *s, int *i)
{
    int j;
    int token;

    if (s[0] == '>')
    {
        if (s[1] &&  s[1] == '>')
            token = APPEND;
        else if (!s[1] || (s[1] && s[1] != '>'))
            token = REDIROUT;
    }
    else if (s[0] == '<')
    {
        if (s[1] && s[1] == '<')
            token = HEREDOC;
        else if (!s[1] || (s[1] && s[1] != '<'))
            token = REDIRIN;
    }
    else if (s[0] == '|')
        token = PIPE;
    j  = (token == REDIROUT) + 2 * (token == APPEND || token == HEREDOC)\
    + (token == REDIRIN) + (token == HEREDOC) + (token == PIPE);
    add_node(&info.node, new_node(ft_strndup(s, j), *i, token));
    *i += j;
}

void    parse(char *s)
{
    int i;
	char	*tmp;

    i = 0;
	tmp = ft_strndup(s, ft_strlen(s));
    while (tmp && tmp[i])
    {
        if (tmp[i] && (tmp[i] == '|' || tmp[i] == '>' || tmp[i] == '<'))
            parse_operators(&tmp[i], &i);
        if (tmp[i] && (tmp[i] == '"' || tmp[i] == '\''))
            parse_quotes(&tmp[i],  &i);
        else if (!isspace(tmp[i]))
            parse_words(&tmp[i], &i);
        i += (tmp[i] != '\0');

    }
	return(free(tmp));
}


int main()
{
    char *input;
	t_node *node;

	input = readline("$$: ");
    parse(input);
    node = info.node;
	while (node)
	{
		printf("node {\nstr = [%s]\nidx = %d\ntype = %d\n}\n", node->s, node->idx, node->type);
		node = node->next;
	}
}