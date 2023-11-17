/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 19:44:06 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/16 21:02:09 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		isemptyquote(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (insidequotes(str, i) == 3)
			return (1);
		i++;
	}
	return (0);
}

char **addquoted(char **str, char **quotetab)
{
	int		i;
	int		j;
	int		k;
	char	**line;
	
	i = 0;
	j = 0;
	k = 0;

	if (isemptyquote(str) == 1)
	{
		freedoubletab(str);
		return (NULL);
	}
	line = malloc((sizeofdoubletab(str) + 1) * sizeof (char *));
	while (str[i])
	{
		while (str[i] && (str[i][0] == '\"' || str[i][0] == '\''))
			i++;
		if (str[i] && insidequotes(str, i) == 0)	
			dupcmd(line, str, &k, &i);
		else if (str[i] && insidequotes(str, i) != 0)
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
	if (!cmd[0])
	{
		free(cmd);
		return (NULL);
	}
	return (cmd);
}

int	testtab(char **str, int len)
{
	int	i;
	int	count;

	i = 0;
	count = 0; 
	while (i < len)
	{
		if (str[i] == NULL)
			count ++;
		i++;
	}
	if (count == i)
		return (1);
	return (0);
}

void	freecreations(char *str, char **line, char **quote, char **paths)
{
	if (line)
		freedoubletab(line);
	if (quote)
		freedoubletab(quote);
	if (paths)
		freedoubletab(paths);
	free(str);	
}
//remplir la struct tmtc
int	fillcmd(char *str, char **envp, t_cmd *cmd)
{
	char	**line;
	char	**quote;
	char	**paths;
	char	*spaced;
	
	paths = findpath(envp);
	spaced = expanding(str, envp);
	quote = sortquotes(spaced);
	spaced = spaceit(spaced);
	line = ft_split(spaced, ' ');
	if (!(line = addquoted(line, quote)))
	{
		freecreations(spaced, line, quote, paths);
		return (-1);
	}
	cmd->hd = malloc(countredir(line) * sizeof(int));
	cmd->redir = countredir(line);
	cmd->redir_type = sortredir(line, cmd->hd);
	cmd->input_file = sortfiles(line, '<');
	cmd->output_file = sortfiles(line, '>');
	cmd->redir_in = countfiles(line, '<');
	cmd->redir_out = countfiles(line, '>');
	cmd->cmd = findcmd(line);
	if (cmd->cmd)
		cmd->path = sendpath(cmd->cmd[0], paths);
	else if (!cmd->cmd)
		cmd->path = NULL;
	freecreations(spaced, line, quote, paths);
	return (0);
}
//separer et stocker les infos de la ligne dans la struct
int	parse(t_mini *mini, char *line)
{
	char	**piped;
	int		nbr = 0;
	int		i = 0;
	
	if (checklineerr(line))
		return (-1);
	if (ispipe(line) == 0)
	{
		mini->cmds = malloc(sizeof (t_fill) * 2);
		if (fillcmd(ft_strdup(line), mini->envp, &mini->cmds[0]) != 0)
		{
			free (mini->cmds);
			return (-1);
		}
		return (1);
	}
	else if (ispipe(line))
	{
		mini->cmds = malloc(sizeof (t_fill) * (ispipe(line) + 2));
		piped = ft_split(line, '|');
		while (piped[i])
		{	
			if (fillcmd(piped[i], mini->envp, &mini->cmds[nbr]) != 0)
			{
				free (mini->cmds);
				return (-1);
			}
			nbr++;
			i++;
		}
		freedoubletab(piped);
		return(ispipe(line) + 1);
	}
	return (-1);
}
