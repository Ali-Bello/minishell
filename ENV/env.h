#ifndef ENV_H
#define ENV_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct s_env
{
	char			*var;
	char			*val;
	struct s_env	*next;
}	t_env;


void add_env(t_env **env, t_env *new_env);
t_env *new_env(char *s);
void del_env(t_env **env, char *var);
void free_env(t_env *env);

char *get_val(char *s);
char *get_var(char *s);
t_env *creat_env(char **env);

char *ft_strndup(char *str, int size);
int ft_strcmp(char *s, char *s1);
int ft_strlen(char *s);

void export_f(t_env **env_l, char **env);
void unset_f(t_env **env_l, char **env);
void env_f(t_env *env);
#endif