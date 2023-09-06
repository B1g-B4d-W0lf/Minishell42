/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:33:26 by wfreulon          #+#    #+#             */
/*   Updated: 2023/09/06 00:40:42 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*display(void)
{
	char	*input;

	input = readline("minishell ➤ ");
	return (input);
}

void	ft_sighandler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr("\n");
		display();
		signal(SIGINT, ft_sighandler);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	
	(void)argc;
	(void)argv;
	mini.paths = findpath(envp);
	mini.exit = 0;
	while (mini.exit == 0)
	{
		//signal(SIGINT, ft_sighandler);
		mini.input = display();
		if (mini.input != NULL && *mini.input != '\0')
		{
			add_history(mini.input);
			parse(&mini);
		}
		if (!ft_strncmp(mini.input, "exit", 4))
			mini.exit = 1;
	}
}
