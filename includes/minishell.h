/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 19:52:14 by aderraj           #+#    #+#             */
/*   Updated: 2024/11/11 19:44:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

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

typedef enum e_token
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
}					t_token;

typedef struct s_redir
{
	t_token			mode;
	char			*file;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	t_redir			*redirections;
}					t_cmd;

typedef struct s_list
{
	char			*s;
	int				expand_flag;
	int				amibiguous_redir;
	t_token			type;
	t_cmd			data;
	struct s_list	*sub_list;
	struct s_list	*prev;
	struct s_list	*next;
}					t_list;

typedef struct s_expand
{
	char			*str;
	int				i;
	char			*res;
	int				res_idx;
	int				res_size;
	int				quotes_flags[2];
}					t_expand;

typedef struct s_wildcard
{
	DIR				*dir;
	struct dirent	*entry;
	size_t			name_len;
	bool			flag;
	char			**fragments;
	char			*pattern;
	char			*current_dir;
	t_list			*node;
}					t_wildcard;

typedef struct s_tree
{
	t_token			type;
	t_cmd			data;
	struct s_tree	*sub_tree;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

t_list				*new_node(char *s, int type);
void				add_node(t_list **node, t_list *new_node);

char				*expand_rm_quotes(t_list *node, char *s);
void				append_words(t_list *node, t_expand *params, char *value);
void				parse_operators(t_list **list, char *s, int *i);
void				parse_words(t_list **list, char *s, int *i);
void				parse_quotes(char *s, int *i);
void				expand_wildcards(t_expand *params, t_list *node);
char				*extend_string(t_expand *params);
t_list				*lexer(char *s);
int					ft_isspace(char c);
int					is_operator(char c);
char				*append_value(t_expand *params, char *value);

char				*get_pattern(char *str, int idx);
void				add_first_filename(t_expand *params, char *match,
						int match_len);
void				add_match(t_expand *params, t_wildcard *specs);
void				print_list(t_list *list);
t_tree				*convert_to_ast(t_list *list);
void				free_list(t_list *list);
void				free_tree(t_tree *tree);
char				**extend_array(char **arr, char *new, int i, int *size);
int					get_args_count(t_list *list);
void				free_array(char **arr);
#endif