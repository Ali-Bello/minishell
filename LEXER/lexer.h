/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 03:20:20 by marvin            #+#    #+#             */
/*   Updated: 2024/10/13 03:20:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define BLUE "\x1b[34m"
# define YELLOW "\x1b[33m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define RESET "\x1b[0m"
# define BOLD "\x1b[1m"
# define ITALIC "\x1b[3m"
# define UNDERLINE "\x1b[4m"

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
    e_token  type;
    struct s_list *next;
} t_list;

typedef struct s_expand
{
    char *str;
    int i;
    char *res;
    int res_idx;
    int res_size;
}   t_expand;

t_list *new_node(char *s, int type);
void add_node(t_list **node, t_list *new_node);

char *expand_and_remove_quotes(char *s);
void    parse_operators(t_list **list, char *s, int *i);
void    parse_words(t_list **list, char *s, int *i);
void    parse_quotes(char *s, int *i);
void expand_wildcards(t_expand *params);
char    *extend_string(t_expand *params);
char	*ft_strjoin(char const *s1, char const *s2);
t_list    *lexer(char *s);
void    *ft_memset(void *b, int c, size_t len);
char *ft_strndup(char *str, int size);
size_t	ft_strlen(const char *s);
#endif