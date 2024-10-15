/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 04:39:21 by marvin            #+#    #+#             */
/*   Updated: 2024/10/15 04:39:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void add_node(t_lexer_list **node, t_lexer_list *new_node)
{
	t_lexer_list *tmp;

	tmp = *node;
	if (*node == NULL)
		*node = new_node;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

t_lexer_list *new_node(char *s, int type)
{
	t_lexer_list *node;

	node = malloc(sizeof(t_lexer_list));
	if (node == NULL)
		return (NULL);
	node->type = type;
	node->s = s;
	node->next = NULL;
	return (node);
}
