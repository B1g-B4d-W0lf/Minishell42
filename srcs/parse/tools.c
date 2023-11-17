/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:51:21 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/16 19:54:05 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
