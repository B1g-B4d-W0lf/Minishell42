/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 20:21:55 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/22 16:03:56 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isemptyquote(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i][j])
		{
			if (str[i][j] != '\"' && str[i][j] != '\'')
			{
				if (insidequotes(str, i, j) == 3)
					return (1);
			}
			j++;
		}
		i++;
		j = 0;
	}
	return (0);
}

void	ft_elseifnorm(char **str, char **line, char **quotetab, int *t)
{
	dupcmdquote(line, quotetab, &t[2], &t[1]);
	t[0]++;
	while (str[t[0]] && whilequote(str, t[0]))
		t[0]++;
}

char	**addquoted(char **str, char **quotetab)
{
	int		*t;
	char	**line;

	if (isemptyquote(str) == 1)
		return (freedoubletab(str), NULL);
	t = malloc(3 * sizeof(int));
	line = malloc((sizeofdoubletab(str) + 1) * sizeof (char *));
	if (!t || !line)
		return (NULL);
	t[0] = 0;
	t[1] = 0;
	t[2] = 0;
	while (str[t[0]])
	{
		if (str[t[0]] && !whilequote(str, t[0]))
			dupcmdquote(line, str, &t[2], &t[0]);
		else if (str[t[0]] && whilequote(str, t[0]))
			ft_elseifnorm(str, line, quotetab, t);
	}
	fillnull(line, &t[2], (sizeofdoubletab(str)));
	freedoubletab(str);
	return (free(t), line);
}

char	**execfindcmdredir(char **str, char **cmd)
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
					if ((str[i - 1][0] == '<' || str[i - 1][0] == '>'))
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

char	**findcmd(char **str)
{
	char	**cmd;

	cmd = malloc((sizeofdoubletab(str) + 1) * sizeof(char *));
	if (!cmd)
		return (NULL);
	cmd = execfindcmdredir(str, cmd);
	if (!cmd[0])
	{
		free(cmd);
		return (NULL);
	}
	return (cmd);
}
