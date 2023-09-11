/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:33:26 by wfreulon          #+#    #+#             */
/*   Updated: 2023/09/11 17:47:02 by wfreulon         ###   ########.fr       */
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

int	checknotoken(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' || str[i] == ';' || str[i] == '!')
			return (1);
		i++;
	}
	return (0);
}

int	checkline(t_mini *mini)
{
	char *str;

	str = mini->input;
	if (checknotoken(str))
	{
		ft_printf("invalid token\n");
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	
	(void)argc;
	(void)argv;
	mini.paths = findpath(envp);
	mini.exit = 0;
	mini.input = NULL;
	while (mini.exit == 0)
	{
		//signal(SIGINT, ft_sighandler);
		mini.input = display();
		if (mini.input != NULL && *mini.input != '\0')
		{
			add_history(mini.input);
			if (checkline(&mini))
			{
				mini = parse(&mini);
				printf("%s\n", mini.cmds[0]->cmd[0]);
				cleanleak(&mini);
			}
		}
		if (!ft_strncmp(mini.input, "exit", 4))
			mini.exit = 1;
	}
	freedoubletab(mini.paths);
}
