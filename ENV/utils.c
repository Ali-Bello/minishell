#include "env.h"

char *ft_strndup(char *str, int size)
{
    char    *s;
    int     i;
    int     len;
    
    i = 0;
    len = ft_strlen(str);
    size = (size * (len >= size)) + (len * (len < size));
    s = malloc ((size + 1) * sizeof(char));
    while (str && str[i] && i < size)
    {
        s[i] = str[i];
        i++;
    }
    s[i] = 0;
    return (s);
}

int ft_strlen(char *s)
{
    int i;

    i = 0;
    while (s && s[i])
        i++;
    return (i);
}
int ft_strcmp(char *s, char *s1)
{
    int i;

    i = 0;
    while(s && s1 && s[i] == s1[i] && s[i] && s1[i])
        i++;
    return(s[i] - s1[i]);
}

char *get_val(char *s)
{
	int i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '=')
			return (ft_strndup(&s[i + 1], ft_strlen(&s[i + 1])));
		i++;
	}
	return (NULL);
}

char *get_var(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '=')
			return (ft_strndup(s, i));
		i++;
	}
	return (NULL);
}