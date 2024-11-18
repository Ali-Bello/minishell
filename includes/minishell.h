/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 19:52:14 by aderraj           #+#    #+#             */
/*   Updated: 2024/11/18 23:13:26 by marvin           ###   ########.fr       */
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
	bool			to_sort;
	t_list			*idx_node;
}					t_expand;

typedef struct s_wildcard
{
	char			**segments;
	char			*pattern;
	char			*ptr;
	char			*start;
	char			*curr_path;
	char			*next_path;
	int				num_segments;
	int				idx;
	int				len;
	bool			skip_hidden;
	bool			add_slash;
	bool			match_found;
	t_expand		*params;
	t_list			*node;
	t_list			*last_node;
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

void				expand_rm_quotes(t_list *node, char *s);
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

char				*get_pattern(t_expand *params);
void				add_match(t_wildcard *rules, char *str);
void				print_list(t_list *list);
t_tree				*convert_to_ast(t_list *list);
void				free_list(t_list *list);
void				free_tree(t_tree *tree);
char				**extend_array(char **arr, char *new, int i, int *size);
int					get_args_count(t_list *list);
void				free_array(char **arr);
void				match_patterns(t_expand *params, t_wildcard *specs);
char				*get_segment(char *s, int *idx, int len);
void				set_segments(t_wildcard *rules);
void				swap_strings(t_list *a, t_list *b);
void				final_touches(t_wildcard *rules);
t_list				*insert_node(t_list *start, t_list *new_node);
void				sort_fnames(t_list *start, t_list *end);
char				*construct_filename(t_wildcard *rules, char *s);
void				set_position(t_tree *stats[]);
void				arrange_nodes(t_list *list[3], t_redir *redirections);
void				merge_nodes(t_list *list, t_redir *redirs);
t_list				*get_redirections(t_list *list, t_list *current,
						t_redir **redirect);
void				parser(t_list *list);
void				print_ast(t_tree *node, int level);

#endif