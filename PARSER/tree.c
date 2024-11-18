/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 07:54:21 by marvin            #+#    #+#             */
/*   Updated: 2024/11/18 14:50:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * stats array[]:
 * 0 : root of the tree
 * 1 : current command
 * 2 : last operator
 * 3 : last pipe
 * 4 : tmp to store new_nodes
 */

#define ROOT stats[0]
#define CURRENT_CMD stats[1]
#define LAST_OP stats[2]
#define LAST_PIPE stats[3]
#define TMP stats[4]

t_tree	*new_tree_node(t_token type, t_cmd data)
{
	t_tree	*node;

	node = (t_tree *)malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	ft_bzero(node, sizeof(t_tree));
	node->type = type;
	node->data = data;
	if (data.cmd && !*data.cmd)
	{
		free(node->data.cmd);
		node->data.cmd = NULL;
	}
	return (node);
}

void	insert_pipe(t_cmd data, t_tree *stats[])
{
	TMP = new_tree_node(PIPE, data);
	if (!ROOT)
		TMP->left = CURRENT_CMD;
	else if (LAST_OP)
	{
		LAST_OP->right = CURRENT_CMD;
		TMP->left = LAST_OP;
		LAST_OP = NULL;
	}
	else
	{
		if (LAST_PIPE)
			LAST_PIPE->right = CURRENT_CMD;
		else
			ROOT->right = CURRENT_CMD;
		TMP->left = ROOT;
	}
	ROOT = TMP;
	LAST_PIPE = TMP;
	CURRENT_CMD = NULL;
}

void	insert_logical_op(t_list *node, t_tree *stats[])
{
	TMP = new_tree_node(node->type, node->data);
	if (!ROOT)
	{
		TMP->left = CURRENT_CMD;
		ROOT = TMP;
	}
	else if (LAST_PIPE)
	{
		LAST_PIPE->right = CURRENT_CMD;
		TMP->left = ROOT;
		LAST_PIPE = NULL;
	}
	else if (LAST_OP)
	{
		LAST_OP->right = CURRENT_CMD;
		TMP->left = ROOT;
	}
	else
	{
		ROOT->right = CURRENT_CMD;
		TMP->left = ROOT;
	}
	ROOT = TMP;
	LAST_OP = TMP;
	CURRENT_CMD = NULL;
}

t_tree	*set_root_node(t_tree *stats[])
{
	if (CURRENT_CMD && LAST_OP)
		LAST_OP->right = CURRENT_CMD;
	else if (CURRENT_CMD && ROOT)
	{
		if (LAST_PIPE)
			LAST_PIPE->right = CURRENT_CMD;
		else
			ROOT->right = CURRENT_CMD;
	}
	else if (CURRENT_CMD && !ROOT)
		ROOT = CURRENT_CMD;
	return (ROOT);
}

t_tree	*convert_to_ast(t_list *list)
{
	t_tree	*stats[5];

	ft_bzero(stats, sizeof(stats));
	while (list && list->s)
	{
		if (list->type == CMD)
			CURRENT_CMD = new_tree_node(CMD, list->data);
		else if (list->type == PIPE)
			insert_pipe(list->data, stats);
		else if (list->type == AND || list->type == OR)
			insert_logical_op(list, stats);
		else if (list->type == PARENTHESIS)
		{
			TMP = new_tree_node(PARENTHESIS, list->data);
			TMP->sub_tree = convert_to_ast(list->sub_list);
			CURRENT_CMD = TMP;
		}
		list = list->next;
	}
	return (set_root_node(stats));
}
