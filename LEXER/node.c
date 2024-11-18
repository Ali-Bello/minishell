/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 04:39:21 by marvin            #+#    #+#             */
/*   Updated: 2024/11/18 01:46:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_node(t_list **node, t_list *new_node)
{
	t_list	*tmp;

	tmp = *node;
	if (*node == NULL)
		*node = new_node;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_node;
		new_node->prev = tmp;
	}
}

t_list	*new_node(char *s, int type)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	ft_bzero(node, sizeof(t_list));
	node->type = type;
	node->s = s;
	return (node);
}

t_list	*insert_node(t_list *start, t_list *new_node)
{
	if (start)
	{
		new_node->next = start->next;
		start->next = new_node;
	}
	return (new_node);
}

void	swap_strings(t_list *a, t_list *b)
{
	char	*tmp;

	tmp = a->s;
	a->s = b->s;
	b->s = tmp;
}

void	sort_fnames(t_list *start, t_list *end)
{
	t_list	*ptr1;
	t_list	*lptr;
	int		swapped;

	if (!start)
		return ;
	lptr = NULL;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr1 = start;
		while (ptr1->next != lptr && ptr1->next != end)
		{
			if (ft_strncmp(ptr1->s, ptr1->next->s, ft_strlen(ptr1->s) + 1) > 0)
			{
				swap_strings(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}
