#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_node
{
    char *s;
    int index;
    int type;
    struct s_node *next;
} t_node;


// type == 1 == |
// type == 2 == <<
// type == 3 == >>
// type == 4 == <
// type == 5 == >
// type == 6 == word

t_node *new_node(char *s, int start, int end, int type);
void add_node(t_node **node, t_node *new_node);
void swap_node(t_node *a, t_node *b);
void sort_node(t_node **node);


void parse_words(char *s, t_node **node);
t_node *parse_redirection(char *s);
int chechk_re(char *s, int i);
void set_space(char *s);
t_node *parse(char *s);

void    *ft_memset(void *b, int c, size_t len);
char *ft_strndup(char *str, int size);
int   ft_strlen(char *s);
#endif