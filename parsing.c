/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 19:44:06 by wfreulon          #+#    #+#             */
/*   Updated: 2023/10/27 19:14:16 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//trouver si une string contient un char donné
int	findchar(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
int countcmd(char **str)
{
	int	i;
	int	j;
	int	count;
	
	i = 0;
	j = 0;
	count = 0;
	while (str[i])
	{
		if (str[i][j] != '<' && str[i][j] != '>')
		{
			if (str[i + 1] && str[i + 1][j] != '<')
			{
				if (str[i - 1] && (str[i - 1][j] == '<' || str[i - 1][j] == '>'))
					i++;
				while (str[i] && str[i][j] != '<' && str[i][j] != '>')
				{
					count++;
					i++;
				}
			}
		}
		i++;
	}
	return (count);
}

char **findcmd(char **str)
{
	int		i;
	int		j;
	int		k;
	char	**cmd;
	
	i = 0;
	j = 0;
	k = 0;
	cmd = malloc((countcmd(str) + 1) * sizeof(char *));
	if (!cmd)
		return(NULL);
	while (str[i])
	{
		if (str[i][j] != '<' && str[i][j] != '>')
		{
			if ((!str[i + 1]) || (str[i + 1] && str[i + 1][j] != '<'))
			{
				if (str[i - 1] && (str[i - 1][j] == '<' || str[i - 1][j] == '>'))
					i++;
				while (str[i] && str[i][j] != '<' && str[i][j] != '>')
				{
					cmd[k] = ft_strdup(str[i]);
					k++;
					i++;
				}
			}
		}
		if (str[i + 1])
			i++;
		else 
			break ;
	}
	printf("cmd :%s\n", cmd[0]);
	return (cmd);
}

//remplir la struct tmtc
t_cmd	*fillcmd(char *str, int nbr, char **paths)
{
	t_cmd	*cmd;
	char	**line;
	
	cmd = malloc(sizeof (t_cmd));
	if (!cmd)
		return (NULL);
	cmd->quote = sortquotes(str);
	line = ft_split(str, ' ');
	cmd->infile = sortfiles(line, '<');
	cmd->outfile = sortfiles(line, '>');
	cmd->cmd = line;
	cmd->nbr = nbr;
	cmd->redir = countredir(line);
	cmd->redirtype = sortredir(line);
	cmd->redin = countfiles(line, '<');
	cmd->redout = countfiles(line, '>');
	cmd->path = sendpath(line[0], paths);
	//freedoubletab(line);
	return (cmd);
}
//separer et stocker les infos de la ligne dans la struct
t_mini	parse(t_mini *mini, char **envp)
{
	char	**piped;
	t_cmd	**cmd;
	int		nbr = 0;
	int		i = 0;
	
	cmd = NULL;
	mini->paths = findpath(envp);
	if (ispipe(mini->input) == 0)
	{
		cmd = malloc(sizeof (t_cmd) * 2);
		*cmd = fillcmd(mini->input, nbr, mini->paths);
		mini->cmds = cmd;
		mini->cmds[1] = NULL;
	}
	else if (ispipe(mini->input))
	{
		cmd = malloc(sizeof (t_cmd) * (ispipe(mini->input) + 1));
		piped = ft_split(mini->input, '|');
		while (piped[i])
		{	
			cmd[nbr] = fillcmd(piped[i], nbr, mini->paths);
			nbr++;
			i++;
		}
		freedoubletab(piped);
		mini->cmds = cmd;
		mini->cmds[nbr] = NULL;
	}
	return (*mini);
}

