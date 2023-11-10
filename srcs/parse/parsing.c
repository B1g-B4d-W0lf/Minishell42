/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 19:44:06 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/10 23:30:01 by wfreulon         ###   ########.fr       */
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
			while (str[i] && str[i][0] != '\"' && str[i][0] != '\'')
				i++;
		}
	}
	fillnull(cmd, &k, sizeofdoubletab(str));
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
			if (((str[i + 1]) && str[i + 1][0] != '<')
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
						while (str[i] && str[i][0] != '\"' && str[i][0] != '\'')
							i++;
					}
				}
			}
		}
		if (str[i] && str[i + 1])
			i++;
		else 
			break;
	}
	fillnull(cmd, &k, sizeofdoubletab(str));
	return (cmd);
}

char **findcmd(char **str, char **quotetab, char *spaced)
{
	int		pos;
	char	**cmd;
	
	pos = 0;
	cmd = malloc((sizeofdoubletab(str) + 1) * sizeof(char *));
	if (!cmd)
		return(NULL);
	if (!findchar(spaced, '<') && !findchar(spaced, '>'))
		cmd = execfindcmdnoredir(str, quotetab, cmd, pos);
	else if (findchar(spaced, '<') || findchar(spaced, '>'))
		cmd = execfindcmdredir(str, quotetab, cmd, pos);
	return (cmd);
}
//remplir la struct tmtc
t_cmd	fillcmd(char *str, char **envp, t_cmd *cmd)
{
	char	**line;
	char	**quote;
	char	**paths;
	
	paths = findpath(envp);
	str = expanding(str, envp);
	quote = sortquotes(str);
	str = spaceit(str);
	line = ft_split(str, ' ');
	cmd->input_file = sortfiles(line, '<');
	cmd->output_file = sortfiles(line, '>');
	cmd->redir = countredir(line);
	cmd->redir_type = sortredir(line);
	cmd->redir_in = countfiles(line, '<');
	cmd->redir_out = countfiles(line, '>');
	cmd->cmd = findcmd(line, quote, str);
	cmd->path = sendpath(cmd->cmd[0], paths);
	
	freedoubletab(line);
	free(str);
	freedoubletab(quote);
	free(paths);
	return (*cmd);
}
//separer et stocker les infos de la ligne dans la struct
int	parse(t_mini *mini, char *line)
{
	char	**piped;
	int		nbr = 0;
	int		i = 0;
	
	if (ispipe(line) == 0)
	{
		mini->cmds = malloc(sizeof (t_fill) * 2);
		mini->cmds[0] = fillcmd(line, mini->envp, &mini->cmds[0]);
		//mini->cmds[1] = NULL;
		return(1);
	}
	else if (ispipe(line))
	{
		mini->cmds = malloc(sizeof (t_fill) * (ispipe(line) + 1));
		piped = ft_split(line, '|');
		while (piped[i])
		{	
			mini->cmds[nbr] = fillcmd(piped[i], mini->envp, &mini->cmds[nbr]);
			nbr++;
			i++;
		}
		freedoubletab(piped);
		//mini->cmds[nbr] = NULL;
		return(ispipe(line));
	}
	return (-1);
}
