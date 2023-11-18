/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:19:41 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/18 20:17:17 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	insidequotes(char **str, int pos)
{
	int	i;
	int	j;
	int	firstquote;
	
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i][0] == '\'' || str[i][0] == '\"')
		{
			firstquote = i;
			i++;
			j = afterquotes(str, firstquote, pos, &i);
			if (j != 0)
				return (j);
		}
		i++;
	}
	return (0);
}

int	*quotespos(char *str)
{
	int	i;
	int	*tabl;
	int	quote;
	
	i = 0;
	quote = 0;
	tabl = malloc(countquotes(str) * sizeof (int));
	if (tabl == NULL)
		return (NULL);
	while(str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			tabl[quote] = i;
			quote++;
			i++;
			while(str[i] && (str[i] != '\'' && str[i] != '\"'))
				i++;
			if (str[i] == '\'' || str[i] == '\"')
			{
				tabl[quote] = i;
				quote++;
			}
			else if (!str[i])
				break;
		}
		i++;
	}
	return (tabl);
}

char **sortquotes(char *str)
{
	int		i;
	int		j;
	int		k;
	int		len;
	char	**tabl;
	int		*pos;

	i = 0;
	j = 0;
	k = 1;
	len = countquotes(str);
	pos = quotespos(str);
	if (pos == NULL)
		return (NULL);
	tabl = malloc ((countquotes(str) + 1 ) * sizeof (char *));
	if (tabl == NULL)
		return (NULL); 
	while (k < len && i < len)
	{
		if (str[pos[i]] == str[pos[k]])
		{
			tabl[j] = ft_strduppos(str, pos[i], pos[k]);
			k++;
			j++;
			i = k + 1;
		}
		k++;
	}
	free(pos);
	fillnull(tabl, &j, len);
	return(tabl);
}

int	checkposstr(char *str, int firstquote, int pos, int *i)
{
	int	secondquote;

	secondquote = 0;
	while(str[*i] && str[*i] != str[firstquote])
	{
		if (str[*i] == str[firstquote])
			break;
		*i = *i + 1;
	}
	if (str[*i] && str[*i] == str[firstquote])
	{
		secondquote = *i;
		if (pos > firstquote && pos < secondquote && str[firstquote] == '\'')
			return (1);
		else if (pos > firstquote && pos < secondquote && str[firstquote] == '\"')
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
	firstquote = 0;
	while (str[i])
	{
			if (str[i] == '\'' || str[i] == '\"')
			{
				firstquote= i;
				i++;
				j = checkposstr(str, firstquote, pos, &i);
				if (j != 0)
					return (j);
			}
		i++;
	}
	return (j);
}
