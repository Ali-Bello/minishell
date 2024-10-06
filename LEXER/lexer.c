#include "lexer.h"

int chechk_re(char *s, int i)
{
	int type;

	type = (s[i] * (s[i] == '<' || s[i] == '>'));
	if (type)
		i++;
	if(type == s[i])
		return (2);
	else
		return(type);
}

void set_space(char *s)
{
	int	i;
	int	q;

	i = 0;
	q = 0;
	while (s && s[i])
	{
		if ((s[i] == '\'' || s[i] == '"') && q == 0)
			q = s[i];
		else if ((s[i] == '\'' || s[i] == '"') && q == s[i])
            q = 0;
		if ((s[i] == '<' || s[i] == '>' || s[i] == '|') && q == 0)
            s[i] = ' ';
		i++;
	}
}

void parse_words(char *s, t_node **node)
{
	int	i;
	int	q;
	int word;

	i = 0;
	q = 0;
	word = 0;
	set_space(s);
	while (s && i < ft_strlen(s) + 1)
	{
		if ((s[i] == '\'' || s[i] == '"') && q == 0)
			q = s[i];
		else if ((s[i] == '\'' || s[i] == '"') && q == s[i])
            q = 0;
		if (s[i] != ' ' && s[i] && q == 0)
			word++;
        if (q != 0 && s[i])
            word++;
		if (word != 0 && (s[i] == ' ' || s[i] == '\0') && q == 0)
        {
			add_node(node, new_node(s, i - word, word, 6));
			word = 0;
		}
		i++;
	}
}

t_node *parse_redirection(char *s)
{
	int		ar[2];
	t_node	*node;

	ft_memset(ar, 0,sizeof(int) * 2);
	node = NULL;
	while (s && s[ar[0]])
	{
		if ((s[ar[0]] == '"' || s[ar[0]] == '\'') && ar[1] == 0)
			ar[1] = s[ar[0]];
		else if (s[ar[0]] == ar[1])
			ar[1] = 0;
		if (s[ar[0]] == '|' && ar[1] == 0)
			add_node(&node, new_node(s, ar[0], 1, 1));
		if (chechk_re(s, ar[0]) == 2 && ar[1] == 0)
		{
			add_node(&node, new_node(s, ar[0], 2,
				(2 * (s[ar[0]] == '<')) + (3 * (s[ar[0]] == '>'))));
			ar[0]++;
		}
		else if (chechk_re(s, ar[0]) > 0 && ar[1] == 0)
			add_node(&node, new_node(s, ar[0], 1,
				(4 * (s[ar[0]] == '<')) + (5 * (s[ar[0]] == '>'))));
		ar[0]++;
	}
	return (node);
}

t_node *parse(char *s)
{
	char	*tmp;
	t_node	*node;

	tmp = ft_strndup(s, ft_strlen(s));
	node = parse_redirection(tmp);
	parse_words(tmp, &node);
	sort_node(&node);
	return(free(tmp), node);
}

int main ()
{
	char *input;
	t_node *node;

	input = readline("$$: ");
	node = parse(input);
	while(node)
	{
		printf("%s %d %d\n", node->s, node->index, node->type);
		node = node->next;
	}
}