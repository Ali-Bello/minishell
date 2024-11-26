/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 02:23:35 by anamella          #+#    #+#             */
/*   Updated: 2024/11/26 21:49:20 by aderraj          ###   ########.fr       */
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

void	get_input(t_mini *mini)
{
	char	*input;

	while (1)
	{
		signal(SIGINT, sig_hand);
		input = readline(BLUE "mminishell$ " RESET);
		add_history(input);
		if (!input)
			break ;
		if (syntax_check(input) == false)
		{
			free(input);
			continue ;
		}
		mini->list = lexer(input);
		free(input);
		parser(mini->list, mini);
		mini->root = convert_to_ast(mini->list);
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
	int		exit_statu;

	(void)ac;
	(void)av;
	signal(SIGQUIT, SIG_IGN);
	mini = create_mini(ev);
	get_input(mini);
	exit_statu = mini->exit;
	free_mini(mini);
	exit(exit_statu);
	return (0);
}
