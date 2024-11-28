/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 02:23:35 by anamella          #+#    #+#             */
/*   Updated: 2024/11/28 00:42:12 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	g_global_exit = 0;

void	sig_hand(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_global_exit = 130;
}

void	get_input(int ac, char** av,t_mini *mini)
{
	char	*input;

	while (ac | **av)
	{
		signal(SIGINT, sig_hand);
		input = readline(BLUE "mminishell$ " RESET);
		add_history(input);
		if (!input)
		{
			free(input);
			break ;
		}
		mini->list = lexer(input);
		if (check_syntax_errors(mini->list))
		{
			free(input);
			free_list(mini->list);
			mini->list = NULL;
			continue ;
		}
		free(input);
		parser(mini->list, mini->env);
		mini->root = convert_to_ast(mini->list);
		flush_list(mini->list);
		mini->list = NULL;
		read_heredoc(mini->root, mini);
		mini->char_env = convert_env(mini->env);
		g_global_exit = execute_ast(mini->root, mini);
		free_and_reset(mini);
	}
	clear_history();
}

int	main(int ac, char **av, char **ev)
{
	t_mini	*mini;
	int		exit_status;

	signal(SIGQUIT, SIG_IGN);
	mini = create_mini(ev);
	get_input(ac,av,mini);
	exit_status = mini->exit;
	free_mini(mini);
	exit(exit_status);
	return (0);
}
