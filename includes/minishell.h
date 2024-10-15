/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 19:52:14 by aderraj           #+#    #+#             */
/*   Updated: 2024/08/18 01:04:30 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

# define EXIT_STATUS 0
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
    WORD
} e_token;

typedef struct s_lexer_list
{
    char *s;
    e_token  type;
    struct s_lexer_list *next;
} t_lexer_list;

typedef struct s_expand
{
    char *str;
    int i;
    char *res;
    int res_idx;
    int res_size;
}   t_expand;

typedef struct s_wildcard
{
    DIR *dir;
    struct dirent *entry;
    size_t  name_len;
    int recursive_flag;
    bool    flag;
    char    **fragments;
    char    *pattern;
    char    *current_dir;
}   t_wildcard;

t_lexer_list *new_node(char *s, int type);
void add_node(t_lexer_list **node, t_lexer_list *new_node);

char *expand_and_remove_quotes(char *s);
void    parse_operators(t_lexer_list **list, char *s, int *i);
void    parse_words(t_lexer_list **list, char *s, int *i);
void    parse_quotes(char *s, int *i);
void expand_wildcards(t_expand *params, int quotes, int dquotes);
char    *extend_string(t_expand *params);
char	*ft_strjoin(char const *s1, char const *s2);
t_lexer_list    *lexer(char *s);
void    *ft_memset(void *b, int c, size_t len);
char *ft_strndup(char *str, int size);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int ft_isspace(char c);
int is_operator(char c);
char    *append_value(t_expand *params, char *value);

void    recursive_match(t_expand *params, t_wildcard *specs);
int    empty_space(char *s, int idx);
void    construct_path(t_wildcard *specs, char *s);
char    *get_pattern(char *str, int idx);
void    add_first_filename(t_expand *params, char *match, int match_len);
void    add_match(t_expand *params, t_wildcard *specs);
#endif