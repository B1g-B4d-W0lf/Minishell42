/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 19:44:06 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/12 22:08:49 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **addquoted(char **str, char **quotetab)
{
	int		i;
	int		j;
	int		k;
	int		pos;
	char	**line;
	
	i = 0;
	j = 0;
	k = 0;
	pos = 0;
	line = malloc((sizeofdoubletab(str) + 1) * sizeof (char *));
	while (str[i])
	{
		while (str[i] && (str[i][0] == '\"' || str[i][0] == '\''))
			i++;
		pos = i;
		if (str[i] && insidequotes(str, pos) == 0)
			dupcmd(line, str, &k, &i);
		else if (str[i] && insidequotes(str, pos) != 0)
		{
			dupcmd(line, quotetab, &k, &j);
			i++;
			while (str[i] && str[i][0] != '\"' && str[i][0] != '\'')
				i++;
		}
	}
	fillnull(line, &k, (sizeofdoubletab(str)));
	freedoubletab(str);
	return (line);
}

char **execfindcmdredir(char **str, char **cmd)
{
	int	i;
	int	k;
	
	i = 0;
	k = 0;
	while (str[i])
	{
		if ((str[i][0] != '<' && str[i][0] != '>'))
		{
			if (((str[i + 1]) && str[i + 1][0] != '<') || !str[i + 1])
			{
				if (i != 0)
				{
					if (str[i - 1] && (str[i - 1][0] == '<' || str[i - 1][0] == '>'))
						i++;
				}
				while (str[i] && str[i][0] != '<' && str[i][0] != '>')
						dupcmd(cmd, str, &k, &i);
			}
		}
		if (str[i])
			i++;
	}
	fillnull(cmd, &k, sizeofdoubletab(str));
	return (cmd);
}

char **findcmd(char **str)
{
	char	**cmd;
	
	cmd = malloc((sizeofdoubletab(str) + 1) * sizeof(char *));
	if (!cmd)
		return(NULL);
	cmd = execfindcmdredir(str, cmd);
	return (cmd);
}
//remplir la struct tmtc
t_cmd	fillcmd(char *str, char **envp, t_cmd *cmd)
{
	char	**line;
	char	**quote;
	char	**paths;

	paths = findpath(envp);
	str = expanding(str, envp);//voir pour tracer expand/non expand pr les erreurs
	quote = sortquotes(str);//quotes vide à gérer + erreur quote pas fermées
	str = spaceit(str);
	line = ft_split(str, ' ');
	line = addquoted(line, quote);
	cmd->input_file = sortfiles(line, '<');
	cmd->output_file = sortfiles(line, '>');
	cmd->redir = countredir(line);//heredoc à voir ce qui manque 
	cmd->redir_type = sortredir(line);
	cmd->redir_in = countfiles(line, '<');
	cmd->redir_out = countfiles(line, '>');
	cmd->cmd = findcmd(line);
	cmd->path = sendpath(cmd->cmd[0], paths);
	freedoubletab(line);
	free(str);
	freedoubletab(quote);
	freedoubletab(paths);
	return (*cmd);//faire malloc en chaine
}
//separer et stocker les infos de la ligne dans la struct
int	parse(t_mini *mini, char *line)
{
	char	**piped;
	int		nbr = 0;
	int		i = 0;
	
	if (checklineerr(line))// test à faire pour compléter
		return (-1);
	if (ispipe(line) == 0)
	{
		mini->cmds = malloc(sizeof (t_fill) * 2);
		mini->cmds[0] = fillcmd(ft_strdup(line), mini->envp, &mini->cmds[0]);
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
		return(ispipe(line));
	}
	return (-1);
}
