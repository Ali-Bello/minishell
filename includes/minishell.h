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
    WORD,
    CMD,
    REDIRIN,
    REDIROUT,
    APPEND,
    HEREDOC,
    PIPE,
    PARENTHESIS,
    AND,
    OR
} e_token;

typedef struct s_redir
{
    e_token mode;
    char *file;
    struct s_redir *next;
} t_redir;

typedef struct s_cmd
{
    char *cmd;
    char **args;
    t_redir *redirections;
} t_cmd;

typedef union
{
    t_cmd cmd;
    struct s_tree *sub_tree;
} u_token_data;

typedef struct s_list
{
    char *s;
    e_token  type;
    u_token_data data;
    struct s_list *sub_list;
    struct s_list *prev;
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

typedef struct s_tree
{
    e_token type;
    u_token_data data;
    struct s_tree *parent;
    struct s_tree *left;
    struct s_tree *right;
} t_tree;

t_list *new_node(char *s, int type);
void add_node(t_list **node, t_list *new_node);

char    *expand_rm_quotes(char *s);
void    parse_operators(t_list **list, char *s, int *i);
void    parse_words(t_list **list, char *s, int *i);
void    parse_quotes(char *s, int *i);
void    expand_wildcards(t_expand *params, int quotes, int dquotes);
char    *extend_string(t_expand *params);
t_list    *lexer(char *s);
int     ft_isspace(char c);
int     is_operator(char c);
char    *append_value(t_expand *params, char *value);

void    recursive_match(t_expand *params, t_wildcard *specs);
int    empty_space(char *s, int idx);
void    construct_path(t_wildcard *specs, char *s);
char    *get_pattern(char *str, int idx);
void    add_first_filename(t_expand *params, char *match, int match_len);
void    add_match(t_expand *params, t_wildcard *specs);

t_tree  *convert_to_tree(t_list *list);
#endif