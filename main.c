/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:33:26 by wfreulon          #+#    #+#             */
/*   Updated: 2023/09/13 15:54:39 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//affiche le prompt
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
//symboles pas pris en charge
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
void	printcmds(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		ft_printf("%s\n", cmd[i]);
		i++;
	}
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
				printcmds(mini.cmds[0]->cmd);
				cleanleak(&mini);
			}
		}
		if (!ft_strncmp(mini.input, "exit", 4))
			mini.exit = 1;
	}
	freedoubletab(mini.paths);
}
