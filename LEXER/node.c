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

t_node *new_node(char *s, int start, int end, int type)
{
	t_node *node;

	node = malloc(sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->index =  start;
	node->type = type;
	node->s = ft_strndup(&s[start], end);
	node->next = NULL;
	return (node);
}

void swap_node(t_node *a, t_node *b)
{
	char *s;
	int c;

	if (!a || !b)
		return;
	s = a->s;
	a->s = b->s;
	b->s = s;
	c = a->index;
	a->index = b->index;
	b->index = c;
	c = a->type;
	a->type = b->type;
	b->type = c;
	
}
void sort_node(t_node **node)
{
	if(!node || !*node)
		return;
	t_node *tmp;
	t_node *tmp1;

	tmp = *node;
	while (tmp)
	{
		tmp1 = tmp->next;
		while(tmp1)
		{
			if (tmp->index > tmp1->index)
				swap_node(tmp, tmp1);
			tmp1 = tmp1->next;
		} 
		tmp = tmp->next;
	}
}