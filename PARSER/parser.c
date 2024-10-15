/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 20:05:20 by aderraj           #+#    #+#             */
/*   Updated: 2024/10/15 05:25:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    word_parser(t_lexer_list **node)
{
    (*node)->s = expand_and_remove_quotes((*node)->s);
}

void    parser(t_lexer_list *list)
{
    t_lexer_list *tmp;

    tmp = list;
    while (tmp)
    {
        if (tmp->type == WORD)
            word_parser(&tmp);
        tmp = tmp->next;
    }
}

int main()
{
    char    *buf = readline(BLUE"$$:"RESET);
    t_lexer_list *list = lexer(buf);
    parser(list);
    for (t_lexer_list *tmp = list;  tmp; tmp = tmp->next)
        printf("node {s->[%s], type = [%d]}\n", tmp->s, tmp->type);
    return (0);
}