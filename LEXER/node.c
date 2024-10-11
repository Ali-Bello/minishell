#include "lexer.h"

void add_node(t_list **node, t_list *new_node)
{
	t_list *tmp;

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

t_list *new_node(char *s, int i, int type)
{
	t_list *node;

	node = malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->idx =  i;
	node->type = type;
	node->s = s;
	node->next = NULL;
	return (node);
}
