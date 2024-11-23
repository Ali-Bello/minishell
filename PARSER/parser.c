/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 20:05:20 by aderraj           #+#    #+#             */
/*   Updated: 2024/11/23 22:08:42 by aderraj          ###   ########.fr       */
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
		expand_rm_quotes(list, list->s);
		if (list->s && data->args)
			data->args = extend_array(data->args, list->s, i++, &size);
		tmp = list;
		list = list->next;
		free(tmp->s);
		free(tmp);
	}
	return (list);
}

void	merge_words(t_list *list, t_redir *redirs)
{
	int	size;

	if (list->type == WORD)
		expand_rm_quotes(list, list->s);
	size = get_args_count(list);
	if (size)
	{
		list->data.args = ft_calloc(size + 1, sizeof(char *));
		if (!list->data.args)
			return ;
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
	list->next = NULL;
	append_redirection(redirections, new);
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
				expand_rm_quotes(list->next, list->next->s);
			if (list->next == current)
			{
				replace = add_redir_node(redirect, list);
				if (!replace)
					return (list);
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
	t_list	*tmp[3];
	t_redir	*redirections;

	tmp[0] = list;
	redirections = NULL;
	tmp[1] = list;
	tmp[2] = NULL;
	while (tmp[0])
	{
		arrange_nodes(tmp, &redirections);
		if (tmp[0])
			tmp[0] = tmp[0]->next;
	}
}
/**
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
			printf("       data\
				-> cmd.redirections = {mode = [%d],file = [%s]}\n", tmp2->mode,
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
		if (node->data.cmd && node->data.args)
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
		for (t_redir *tmp2 = node->data.redirections; tmp2;\
			tmp2 = tmp2->next)
				printf(" redirections = {mode = [%d], file = [%s]\n",
					tmp2->mode, tmp2->file);
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
	char	*buf;
	t_list	*list;
	t_tree	*root;

	buf = readline(BLUE "$$:" RESET);
	list = lexer(buf);
	parser(list);
	// print_list(list);
	root = convert_to_ast(list);
	print_ast(root, 0);
	free_list(list);
	free_tree(root);
	free(buf);
	return (0);
}
// **/
