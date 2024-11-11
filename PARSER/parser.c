/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 20:05:20 by aderraj           #+#    #+#             */
/*   Updated: 2024/11/11 19:40:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*get_args(t_list *list, t_cmd *data, int size)
{
	int		i;
	t_list	*tmp;

	i = 1;
	while (list && list->type == WORD)
	{
		list->s = expand_rm_quotes(list, list->s);
		if (list->s && data->args)
			data->args = extend_array(data->args, list->s, i++, &size);
		tmp = list;
		list = list->next;
		free(tmp->s);
		free(tmp);
	}
	return (list);
}

void	merge_nodes(t_list *list, t_redir *redirs)
{
	int	size;

	list->s = expand_rm_quotes(list, list->s);
	size = get_args_count(list);
	if (size)
	{
		list->data.args = malloc(sizeof(char *) * (size + 1));
		if (!list->data.args)
			return ;
		list->data.args[size] = NULL;
	}
	if (list->s && size)
	{
		list->data.cmd = ft_strdup(list->s);
		list->data.args[0] = list->data.cmd;
		if (!list->data.cmd)
			return ;
	}
	list->data.redirections = redirs;
	list->type = CMD;
	list->next = get_args(list->next, &list->data, size);
}

t_list	*add_redir_node(t_redir **redirections, t_list *list)
{
	t_redir	*new;
	t_list	*tmp;

	tmp = NULL;
	if (!list->next || list->next->type != WORD)
		return (list->next);
	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->mode = list->type;
	new->next = NULL;
	tmp = list->next->next;
	new->file = ft_strdup(list->next->s);
	free(list->next->s);
	free(list->next);
	while ((*redirections) && (*redirections)->next)
		*redirections = (*redirections)->next;
	if (*redirections)
		(*redirections)->next = new;
	else
		*redirections = new;
	return (tmp);
}

t_list	*get_redirections(t_list *list, t_list *current, t_redir **redirect)
{
	t_list	*replace;

	replace = current;
	while (list && list->type != PIPE && list->type != PARENTHESIS
		&& list->type != AND && list->type != OR)
	{
		if (list && (list->type == REDIRIN || list->type == REDIROUT
				|| list->type == APPEND || list->type == HEREDOC))
		{
			if (list->type != HEREDOC && list->next)
			{
				list->next->amibiguous_redir = 1;
				list->next->s = expand_rm_quotes(list->next, list->next->s);
			}
			if (list->next == current)
			{
				replace = add_redir_node(redirect, list);
				list->next = replace;
			}
			else
				list->next = add_redir_node(redirect, list);
		}
		list = list->next;
	}
	return (replace);
}

void	parser(t_list *list)
{
	t_list	*tmp;
	t_redir	*redirections;
	t_list	*start;

	tmp = list;
	redirections = NULL;
	start = tmp;
	while (tmp)
	{
		if (tmp && tmp->type == WORD)
		{
			tmp = get_redirections(start, tmp, &redirections);
			merge_nodes(tmp, redirections);
			redirections = NULL;
		}
		else if (tmp && tmp->type == PARENTHESIS)
		{
			tmp->sub_list = lexer(tmp->s);
			parser(tmp->sub_list);
		}
		else if (tmp->type == PIPE || tmp->type == AND || tmp->type == OR)
			start = tmp->next;
		if (tmp)
			tmp = tmp->next;
	}
}


void	print_list(t_list *list)
{
	for (t_list *tmp = list; tmp; tmp = tmp->next)
	{
		printf("node -> {type = [%d], s = [%s]}\n", tmp->type, tmp->s);
		if (tmp->data.cmd)
			printf("       data -> cmd = [%s]\n", tmp->data.cmd);
		for (int i = 0; tmp->data.args && tmp->data.args[i]; i++)
			printf("       data -> cmd.args = [%s]\n", tmp->data.args[i]);
		for (t_redir *tmp2 = tmp->data.redirections; tmp2; tmp2 = tmp2->next)
			printf("       data -> cmd.redirections = {mode = [%d],\
				file = [%s]\n",
					tmp2->mode,
					tmp2->file);
		if (tmp->sub_list)
		{
			printf(GREEN "---SUB_list\n" RESET);
			print_list(tmp->sub_list);
			printf(GREEN "---END OF SUB_list\n" RESET);
		}
	}
}
void	print_ast(t_tree *node, int level)
{
	if (!node)
		return ;
	// Print indentation based on the level of the node in the tree
	for (int i = 0; i < level; i++)
	{
		printf("    ");
	}
	switch (node->type)
	{
	case CMD:
		printf("CMD: %s", node->data.cmd);
		if (node->data.args)
		{
			printf(" args: ");
			for (int i = 0; node->data.args[i]; i++)
				printf("[%s] ", node->data.args[i]);
		}
		if (node->data.redirections)
		{
			for (t_redir *tmp2 = node->data.redirections; tmp2;\
              tmp2 = tmp2->next)
				printf(" redirections = {mode = [%d], file = [%s]\n",
					tmp2->mode, tmp2->file);
		}
		printf("\n");
		break ;
	case PIPE:
		printf("PIPE\n");
		break ;
	case AND:
		printf("AND\n");
		break ;
	case OR:
		printf("OR\n");
		break ;
	case PARENTHESIS:
		printf("PARENTHESIS\n");
		printf("SUB tree inside parentheses: \n");
		// Print the sub-tree inside the parentheses
		print_ast(node->sub_tree, level + 1);
		printf("END OF SUB tree inside parentheses:\n");
		return ;
	default:
		printf("Unknown node type\n");
	}
	// Recursively print left and right children
	if (node->left)
	{
		printf(GREEN "  left level = %d\n" RESET, level);
		print_ast(node->left, level + 1);
	}
	if (node->right)
	{
		printf(GREEN "  right level = %d\n" RESET, level);
		print_ast(node->right, level + 1);
	}
}

int	main(void)
{
	char *buf = readline(BLUE "$$:" RESET);
	t_list *list;
	list = lexer(buf);
	parser(list);
	// print_list(list);
	t_tree *root = convert_to_ast(list);
	print_ast(root, 0);
	free_list(list);
	free_tree(root);
	return (0);
}