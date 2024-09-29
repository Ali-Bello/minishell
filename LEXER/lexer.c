#include "lexer.h"

t_tokens *new_token(char *str, t_token token)
{
	t_tokens	*tokens;
	
	tokens = malloc(sizeof(t_tokens));
	tokens->next = NULL;
	tokens->str = str;
	tokens->token = token;
	return (tokens);
}
void add_tokens(t_tokens **tokens, t_tokens *new_tokens)
{
	t_tokens	*tmp;

	tmp = *tokens;
	if (*tokens == NULL)
		*tokens = new_tokens;
	else
	{
		while (tmp && tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_tokens;
	}
}
t_tokens *lexer(char *str)
{
	t_tokens	*token;
	int			i;
	int			word;
	
	i = 0;
	word = 0;
	while (str && str[i])
	{
		if (iswhat(str[i]))
		{
			if (iswhat(str[i]) == 5 || iswhat(str[i]) == 6)
			{
				if (is)
			}
			
		}

			
	}
}

// int main ()
// {
// 	t_tokens *token;

// 	token = NULL;
// 	int i = 0;
// 	while (i < 5)
// 	{
// 		add_tokens(&token, new_token("anas", DOUBLE_QUOT));
// 		i++;
// 	}
// 	while (token)
// 	{
// 		printf ("-------------------------\n");
// 		printf ("%s | %d\n", token->str, token->token);
// 		token = token->next;
// 	}
// }