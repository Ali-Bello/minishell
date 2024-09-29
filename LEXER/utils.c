#include "lexer.h"

int iswhat(char c)
{
	int code;

	code = (1 * (c == '\"') + 2 * (c == '\''))
        + (3 * ((c >= 9 && c <= 13) || c == 32))
            +  (4 * (c == '|')) + (5 * (c == '>'))
                + (6 * (c == '<')) + (7 * (c == '$'));
	return (code);
}

int ft_strlen(char *str)
{
    int i;
    
    i = 0;
    while (str && str[i])
        i++;
    return (i);
}

char *ft_strndup(char *str, int size)
{
    char    *s;
    int     i;
    int     len;
    
    i = 0;
    len = ft_strlen(str);
    size = (size * (len >= size)) + (len * (len < size));
    printf("%d\n", size);
    s = malloc ((size + 1) * sizeof(char));
    while (str && str[i] && i < size)
    {
        s[i] = str[i];
        i++;
    }
    s[i] = 0;
    return (s);
}