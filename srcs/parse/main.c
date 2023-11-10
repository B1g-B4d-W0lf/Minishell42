/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:33:26 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/09 19:14:11 by wfreulon         ###   ########.fr       */
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
		if (str[i] == '|' && str[i + 1] == '|')
			return(1);
		if ((str[i] == '>' && str[i + 1] == '<') || (str[i] == '<' && str[i + 1] == '>'))
			return(1);
		if (str[i] == '<' && str[i + 1] == '>' && (str[i + 2] == '>' || str[i + 2] == '<'))
			return (1);
		if (str[i] == '>' && str[i + 1] == '<' && (str[i + 2] == '>' || str[i + 2] == '<'))
			return (1);
		i++;
	}
	if (str[i - 1] == '<' || str[i - 1] == '>' || str[i - 1] == '|')
		return (1);
	return (0);
}
//check si la ligne n'as pas d'erreurs de syntaxe/de mauvais symbole
int	checkline(t_minish *mini)
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
/*void	printcmds(t_minish *mini)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (mini->cmds[i])
	{
		while(mini->cmds[i]->cmd[j])
		{
			ft_printf("cmd %d :%s\n", j, mini->cmds[i]->cmd[j]);
			j++;
		}
		j = 0;
		i++;
	}
	i = 0;
	j = 0;
	while (mini->cmds[i])
	{
		while(mini->cmds[i]->infile[j])
		{
			ft_printf("infile %d :%s\n", j, mini->cmds[i]->infile[j]);
			j++;
		}
		j = 0;
		i++;
	}
	i = 0;
	j = 0;
	while (mini->cmds[i])
	{
		while(mini->cmds[i]->outfile[j])
		{
			ft_printf("outfile %d :%s\n", j, mini->cmds[i]->outfile[j]);
			j++;
		}
		j = 0;
		i++;
	}
	i = 0;
	j = 0;
	while (mini->cmds[i])
	{
		while(mini->cmds[i]->redirtype[j])
		{
			ft_printf("tab %d :%d\n", j, mini->cmds[i]->redirtype[j]);
			j++;
		}
		j = 0;
		i++;
	}
	i = 0;
	j = 0;
	while (mini->cmds[i])
	{
		while(mini->cmds[i]->quote[j])
		{
			printf("quote %d :%s\n", j, mini->cmds[i]->quote[j]);
			j++;
		}
		j = 0;
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minish	mini;
	
	(void)argc;
	(void)argv;
	//mini.paths = findpath(envp);
	mini.exit = 0;
	mini.input = NULL;
	while (mini.exit == 0)
	{
		//signal(SIGINT, ft_sighandler);
		mini.input = display();
		if (!ft_strncmp(mini.input, "exit", 4))
			break ;
		if (mini.input != NULL && *mini.input != '\0')
		{
			add_history(mini.input);
			if (checkline(&mini))
			{
				mini = parse(&mini, envp);
				printcmds(&mini);
				cleanleak(&mini);
			}
		}

	}
	//freedoubletab(mini.paths);
}*/
