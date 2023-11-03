/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 19:44:06 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/03 19:06:28 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **execfindcmdnoredir(char **str, char **quotetab, char **cmd, int pos)
{
	int	i;
	int	j;
	int	k;
	
	i = 0;
	j = 0;
	k = 0;
	while (str[i])
	{
		while (str[i] && (str[i][0] == '\"' || str[i][0] == '\''))
			i++;
		pos = i;
		if (str[i] && insidequotes(str, pos) == 0)
			dupcmd(cmd, str, &k, &i);
		else if (str[i] && insidequotes(str, pos) != 0)
		{
			dupcmd(cmd, quotetab, &k, &j);
			i++;
			pos = i;
			while (str[i] && str[i][0] != '\"' && str[i][0] != '\'')
				i++;
		}
	}
	fillnull(cmd, &k, doubletabsize(str));
	return (cmd);
}

char **execfindcmdredir(char **str, char **quotetab, char **cmd, int pos)
{
	int	i;
	int	j;
	int	k;
	
	i = 0;
	j = 0;
	k = 0;
	while (str[i])
	{
		pos = i;
		if ((str[i][0] != '<' && str[i][0] != '>') || insidequotes(str, pos) != 0)
		{
			pos = i + 1;
			if ((((!str[i + 1]) || (str[i + 1])) && str[i + 1][0] != '<')
				|| insidequotes(str, pos) != 0)
			{
				pos = i - 1;
				if (str[i - 1] && (str[i - 1][0] == '<' || str[i - 1][0] == '>')
				&& insidequotes(str, pos) == 0)
					i++;
				while (str[i] && str[i][0] != '<' && str[i][0] != '>')
				{
					while (str[i] && (str[i][0] == '\"' || str[i][0] == '\''))
						i++;
					pos = i;
					if (str[i] && insidequotes(str, pos) == 0)
						dupcmd(cmd, str, &k, &i);
					else if (str[i] && insidequotes(str, pos) != 0)
					{
						dupcmd(cmd, quotetab, &k, &j);
						i++;
						pos = i;
						while (str[i] && str[i][0] != '\"' && str[i][0] != '\'')
							i++;
					}
				}
			}
		}
		i++;
	}
	fillnull(cmd, &k, doubletabsize(str));
	return (cmd);
}

char **findcmd(char **str, char **quotetab, char *spaced)
{
	int		pos;
	char	**cmd;
	
	pos = 0;
	cmd = malloc((doubletabsize(str) + 1) * sizeof(char *));
	if (!cmd)
		return(NULL);
	if (!findchar(spaced, '<') && !findchar(spaced, '>'))
		cmd = execfindcmdnoredir(str, quotetab, cmd, pos);
	else if (findchar(spaced, '<') || findchar(spaced, '>'))
		cmd = execfindcmdredir(str, quotetab, cmd, pos);
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
	str = spaceit(str);
	line = ft_split(str, ' ');
	cmd->infile = sortfiles(line, '<');
	cmd->outfile = sortfiles(line, '>');
	cmd->nbr = nbr;
	cmd->redir = countredir(line);
	cmd->redirtype = sortredir(line);
	cmd->redin = countfiles(line, '<');
	cmd->redout = countfiles(line, '>');
	cmd->path = sendpath(line[0], paths);
	cmd->cmd = findcmd(line, cmd->quote, str);
	freedoubletab(line);
	free(str);
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
