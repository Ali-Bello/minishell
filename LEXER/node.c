#include "lexer.h"

void add_node(t_node **node, t_node *new_node)
{
	t_node *tmp;

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

t_node *new_node(char *s, int i, int type)
{
	t_node *node;

	node = malloc(sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->idx =  i;
	node->type = type;
	node->s = s;
	node->next = NULL;
	return (node);
}
