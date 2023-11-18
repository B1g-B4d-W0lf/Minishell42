/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 20:21:55 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/18 20:22:50 by wfreulon         ###   ########.fr       */
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
