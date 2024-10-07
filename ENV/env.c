#include "env.h"

t_env *creat_env(char **env)
{
	int		i;
	t_env	*env_l;

	i = 0;
	env_l = NULL;
	if (!env)
		return (NULL);
	while (env[i])
	{
		add_env(&env_l, new_env(env[i]));
		i++;
	}
	return (env_l);
}
void export_f(t_env **env_l, char **env)
{
	int i;

	i = 0;
	while (env && env[i])
	{
		add_env(env_l, new_env(env[i]));
		i++;
	}
}

void unset_f(t_env **env_l, char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		del_env(env_l, env[i]);
		i++;
	}
}
void env_f(t_env *env)
{
	while(env)
	{
		printf("%s=%s\n", env->var, env->val);
		env = env->next;
	}
}
int main(int ac, char **av, char **enve)
{
	t_env *env_l;
	env_l = creat_env(enve);
	if (!ft_strcmp(av[1], "export"))
	{
		export_f(&env_l, &av[2]);
		env_f(env_l);
	}
	if (!ft_strcmp(av[1], "unset"))
	{
		unset_f(&env_l, &av[2]);
		env_f(env_l);;
	}
	if (!ft_strcmp(av[1], "env"))
		env_f(env_l);
	free_env(env_l);
}