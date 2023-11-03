/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:51:21 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/03 14:16:38 by wfreulon         ###   ########.fr       */
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

int	doubletabsize(char **str)
{
	int	i;
	
	i = 0;
	while (str[i])
		i++;
	return (i);
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
	cmd[*i] = ft_strdup(src[*j]);
	*i = *i + 1;
	*j = *j + 1;
}
