/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:19:41 by wfreulon          #+#    #+#             */
/*   Updated: 2023/09/28 22:08:54 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	countquotes(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			count++;
		i++;
	}
	return (count);
}

int	*quotespos(char *str)
{
	int	i;
	int	*tab;
	int	quote;
	
	i = 0;
	quote = 0;
	tab = malloc(countquotes(str) * sizeof (int));
	if (tab == NULL)
		return (NULL);
	while(str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			tab[quote] = i;
			quote++;
			while((str[i] != '\'' || str[i] != '\"') && str[i])
				i++;
			if (str[i] == '\'' || str[i] == '\"')
			{
				tab[quote] = i;
				quote++;
			}
		}
		i++;
	}
	return (tab);
}

int insidequotes(char *str, int c)
{
	int	i;
	int j;
	int	quotes;
	int *pos;
	
	pos = quotespos(str);
	if (pos == NULL)
		return (0);
	i = 0;
	j = 1;
	quotes = countquotes(str);
	while (i < quotes && j <= quotes)
	{
		while (str[pos[i]] != str[pos[j]] && j <= quotes)
			j++;
		if (c > pos[i] && c < pos[j])
			return (1);
		i++;
		j = i + 1;
	}
	free (pos);
	return (0);
}
