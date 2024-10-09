#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef enum s_token
{
    PIPE,
    HEREDOC,
    APPEND,
    REDIRIN,
    REDIROUT,
    WORD
} e_token;

typedef struct s_node
{
    char *s;
    int idx;
    e_token  type;
    struct s_node *next;
} t_node;

typedef struct s_info
{
    t_node  *node;
}   t_info;



// type == 1 == |
// type == 2 == <<
// type == 3 == >>
// type == 4 == <
// type == 5 == >
// type == 6 == word

t_node *new_node(char *s, int i, int type);
void add_node(t_node **node, t_node *new_node);


void    parse_operators(char *s, int *i);
void    parse_quotes(char *s, int *i);
void    parse_words(char *s, int *i);

void    parse(char *s);

void    *ft_memset(void *b, int c, size_t len);
char *ft_strndup(char *str, int size);
int   ft_strlen(char *s);
#endif