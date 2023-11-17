/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:51:21 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/17 08:43:34 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	findchar(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	sizeofdoubletab(char **tabl)
{
	int	i;
	
	i = 0;
	while(tabl[i])
		i++;
	return(i);
}

void	fillnull(char **str, int *i, int len)
{
	while (*i < len)
	{
		str[*i] = NULL;
		*i = *i + 1;
	}
	str[*i] = NULL;
}

char	*dupcmdslash(char *cmd, char **dup)
{
	int		s;
	int		p;
	int		count;
	char	*str;

	s = 0;
	p = 0;
	count = 0;
	if (cmd[0] == '/')
	{
		s = findchar(cmd, '/');
		while (cmd[p] && count < s)
		{
			if (cmd[p] == '/')
				count++;
			p++;
		}
		str = ft_strduppos(cmd, p, ft_strlen(cmd) - 1);
		*dup = ft_strduppos(cmd, 0, p - 1);
	}
	free(cmd);
	return (str);
}

void	dupcmd(char **cmd, char **src, int *i, int *j)
{
	if ((src[*j][0] == '\"' || src[*j][0] == '\'')
		&& src[*j][1] != src[*j][0])
		cmd[*i] = ft_strduppos(src[*j], 1, ft_strlen(src[*j]) - 2);
	else
		cmd[*i] = ft_strdup(src[*j]);
	*i = *i + 1;
	*j = *j + 1;
}

int	ispipe(char *str)
{
	int	i;
	int	pipe;
	
	i = 0;
	pipe = 0;
	while (str[i])
	{
		if (str[i] == '|' && str[i + 1] != '|')
			pipe ++;
		i++;
	}
	return (pipe);
}
