/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:19:41 by wfreulon          #+#    #+#             */
/*   Updated: 2023/10/26 19:21:48 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	countquotes(char *str)
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

int	comparedoublepos(int *pos, int *firstquote, int *secondquote)
{
	if (pos[0] >=  firstquote[0])
	{
		if (pos[0] == firstquote[0])
		{
			if (pos[1] < firstquote[1])
				return (0);
		}
		else
		{
			if (pos[0] <= secondquote[0])
			{
				if (pos[0] == secondquote[0])
				{
					if (pos[1] < secondquote[1])
						return (1);
				}
				else
					return (1);
			}
		}
	}
	return (0);
}

int	afterquotes(char **str, int *firstquote, int *pos)
{
	int	*secondquote;
	int	i;
	int	j;

	secondquote = malloc(2 * sizeof(int));
	i = firstquote[0];
	j = firstquote[1] + 1;
	while (str[i] && str[i][j] != str[firstquote[0]][firstquote[1]])
	{
		while (str[i][j] != str[firstquote[0]][firstquote[1]] && str[i][j])
			j++;
		if (str[i][j] == str[firstquote[0]][firstquote[1]])
			break;
		i++;
		j = 0;
	}
	if (str[i] && str[i][j] == str[firstquote[0]][firstquote[1]])
	{
		secondquote[0] = i;
		secondquote[1] = j;
		if (comparedoublepos(pos, firstquote, secondquote) && str[firstquote[0]][firstquote[1]] == '\'')
			return (free(secondquote), 1);
		else if (comparedoublepos(pos, firstquote, secondquote) && str[firstquote[0]][firstquote[1]] == '\"')
			return (free(secondquote), 2);
		printf("%d, %d\n", pos[0], pos[1]);
	}
	return (free(secondquote), 3);
} */
int	checkpos(char *str, int firstquote, int pos)
{
	int	i;
	int	secondquote;

	i = firstquote;
	secondquote = 0;
	while(str[i] && str[i] != str[firstquote])
	{
		if (str[i] == str[firstquote])
			break;
		i++;
	}
	if (str[i] == str[firstquote])
	{
		secondquote = i;
		if (pos > firstquote && pos < secondquote && str[firstquote] == '\'')
			return (1);
		if (pos > firstquote && pos < secondquote && str[firstquote] == '\"')
			return (2);
	}
	return (3);
}

int	insidequotes(char *str, int pos)
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
				j = checkpos(str, firstquote, pos);
				return(j);
			}
		i++;
	}
	return (0);
}

char **isinquote(char *str)
{
	int		i;
	char	**tab;

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

/*int insidequotes(char *str, int c)
{
	int	i;
	int j;
	int	quotesnbr;
	int *pos;
	
	pos = quotespos(str);
	if (pos == NULL)
		return (0);
	i = 0;
	j = 1;
	quotesnbr = countquotes(str);
	while (i < quotesnbr && j <= quotesnbr)
	{
		while (str[pos[i]] != str[pos[j]] && j <= quotesnbr)
			j++;
		if (c > pos[i] && c < pos[j])
			return (1);
		i++;
		j = i + 1;
	}
	free (pos);
	return (0);
} */
