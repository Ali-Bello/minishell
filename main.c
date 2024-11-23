/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamella <anamella@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 02:23:35 by anamella          #+#    #+#             */
/*   Updated: 2024/11/23 02:23:36 by anamella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
void reset_fd(int fd_in, int fd_out)
{
    dup2(fd_in, 0);
    dup2(fd_out, 1);
}
void free_mini(t_mini *mini)
{
	free_env(mini->env);
	free(mini);
}
t_mini *create_mini(char **env)
{
	t_mini *mini;

	mini = malloc(sizeof(t_mini));
	if (!mini)
		error_msg("malloc fail", NULL, EXIT_FAILURE);
	mini->env = create_env(env);
	mini->char_env = NULL; 
	mini->exit = 0;
	mini->infd = dup(0);
	if (mini->infd == -1)
	{
		free_mini(mini);
		error_msg("dup failed", NULL,EXIT_FAILURE);
	}
	mini->outfd = dup(1);
	if (mini->outfd == -1)
	{
		free_mini(mini);
		error_msg("dup failed", NULL, EXIT_FAILURE);
	}
	return (mini);
}

void read_heredoc(t_tree *root, t_mini *mini)
{
	t_redir *red;
	int		i;

	i = 0;
	if (root == NULL)
		return;
	red = root->data.redirections;
	while (red)
	{
		if (red->mode == HEREDOC)
			red->fd = heredoc(red->file, mini);
		red = red->next;
	}
	read_heredoc(root->left, mini);
	read_heredoc(root->right, mini);
}
int main (int ac, char **av, char **ev)
{
    t_mini *mini;
    t_list  *list;

    (void)ac;
    (void)av;
    mini = create_mini(ev);
    while(1)
    {
        char *input = readline(BLUE"mminishell$ "RESET);
		add_history(input);
		if (!input)
		{
			printf("hoola\n");
			mini->root = NULL;
			free_mini(mini);
			break;
		}
        list = lexer(input);
        parser(list);
        t_tree *root = convert_to_ast(list);
		// print_ast(root, 0);
		// for (t_redir *red = root->data.redirections; red; red = red->next)
			// printf("%s\n", red->file);
		read_heredoc(root, mini);
		mini->root = root;
		mini->exit = execute_ast(root, mini);
		printf("exit == %d\n", mini->exit);
		// for(int i = 0; mini->char_env[i];i++)
		// 	printf("%s\n", mini->char_env[i]);
		// mini->root = NULL;
		// free_(mini->char_env);
		// mini->char_env = create_char_env(mini->env);
        reset_fd(mini->infd, mini->outfd);
		// free(input);
		
    }
	// free_mini(mini);
	return (0);
}