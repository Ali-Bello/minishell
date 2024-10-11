#include "lexer.h"

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

void    *ft_memset(void *b, int c, size_t len)
{
        void    *t;

        t = b;
        while (b && len)
        {
                *((unsigned char *)b++) = (unsigned char)c;
                len--;
        }
        return (t);
}

// int ft_strlen(char *s)
// {
//     int i;

//     i = 0;
//     while (s && s[i])
//         i++;
//     return (i);
// }