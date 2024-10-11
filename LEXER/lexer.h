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
    AND,
    OR,
    PARENTHESIS,
    WILDCARD,
    WORD
} e_token;

typedef struct s_list
{
    char *s;
    int idx;
    e_token  type;
    struct s_list *next;
} t_list;


t_list *new_node(char *s, int i, int type);
void add_node(t_list **node, t_list *new_node);


void    parse_operators(t_list **list, char *s, int *i);
void    parse_words(t_list **list, char *s, int *i);
void    parse_quotes(char *s, int *i);

t_list    *lexer(char *s);

void    *ft_memset(void *b, int c, size_t len);
char *ft_strndup(char *str, int size);
size_t	ft_strlen(const char *s);
#endif