/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 20:15:15 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/18 20:24:33 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checkdollar(char *str)
{
	int	i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$' && (insidequotesstr(str, i) == 2 || insidequotesstr(str, i) == 0))
			count++;
		i++;
	}
	return (count);
}

int totallen(char **str)
{
	int	i;
	int	j;
	int	total;

	i = 0;
	j = 0;
	total = 0;
	while (str[i])
	{
		while (str[i][j])
			j++;
		total += j;
		j = 0;
		i++;
	}
	return (total);
}

char *ft_strduppos(char *src, int start, int end)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(((end - start) + 2) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (src[start] && start <= end)
	{
		dest[i] = src[start];
		i++;
		start++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_sup_join(char *s1, char c, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (0);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	str = malloc(((i + j) + 2) * sizeof (char));
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = c;
	i++;
	str = whilenorm(str, s2, i, j);
	return (str);
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