/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:19:41 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/22 20:10:46 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	insidequotes(char **str, int a, int b)
{
	int	*t;
	int	*pos;
	int	*firstquote;

	firstquote = malloc(2 * sizeof(int));
	t = malloc(3 * sizeof(int));
	pos = malloc(2 * sizeof(int));
	if (!firstquote || !t || !pos)
		return (mallocfailint(t, firstquote, pos));
	t[0] = 0;
	t[1] = 0;
	t[2] = 0;
	pos[0] = a;
	pos[1] = b;
	while (str[t[0]])
	{
		while (str[t[0]][t[1]])
		{
			if (whilenofq(str, pos, firstquote, t))
				return (freeints(firstquote, t, pos));
		}
		t[0]++;
		t[1] = 0;
	}
	return (freeints(firstquote, t, pos));
}

int	*quotespos(char *str)
{
	int	i;
	int	*tabl;
	int	quote;

	i = 0;
	quote = -1;
	tabl = malloc(countquotes(str) * sizeof (int));
	if (tabl == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			tabl[++quote] = i;
			i++;
			while (str[i] && (str[i] != '\'' && str[i] != '\"'))
				i++;
			if (str[i] == '\'' || str[i] == '\"')
				tabl[++quote] = i;
			else if (!str[i])
				break ;
		}
		i++;
	}
	return (tabl);
}

char	**sortquotes(char *str, char **tabl)
{
	int		t[3];
	int		len;
	int		*pos;

	t[0] = 0;
	t[1] = 0;
	t[2] = 1;
	len = countquotes(str);
	pos = quotespos(str);
	if (pos == NULL)
		return (NULL);
	while (t[2] < len && t[0] < len)
	{
		if (str[pos[t[0]]] == str[pos[t[2]]])
		{
			tabl[t[1]] = ft_dupquotes(str, pos[t[0]], pos[t[2]]);
			t[2]++;
			t[1]++;
			t[0] = t[2];
		}
		t[2]++;
	}
	free(pos);
	fillnull(tabl, &t[1], len);
	return (tabl);
}

int	checkposstr(char *str, int firstquote, int pos, int *i)
{
	int	secondquote;

	while (str[*i] && str[*i] != str[firstquote])
	{
		if (str[*i] == str[firstquote])
			break ;
		*i = *i + 1;
	}
	if (str[*i] && str[*i] == str[firstquote])
	{
		secondquote = *i;
		if (pos > firstquote && pos < secondquote && str[firstquote] == '\'')
			return (1);
		else if (pos > firstquote && pos < secondquote
			&& str[firstquote] == '\"')
			return (2);
	}
	else if (!str[*i])
		return (3);
	return (0);
}

int	insidequotesstr(char *str, int pos)
{
	int	i;
	int	j;
	int	firstquote;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			firstquote = i;
			i++;
			j = checkposstr(str, firstquote, pos, &i);
			if (j != 0)
				return (j);
		}
		i++;
	}
	return (j);
}
