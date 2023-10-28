/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:19:41 by wfreulon          #+#    #+#             */
/*   Updated: 2023/10/28 16:48:51 by wfreulon         ###   ########.fr       */
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
} 

int	insidequotes(char **str, int *pos)
{
	int	i;
	int	j;
	int	*firstquote;
	
	i = 0;
	j = 0;
	firstquote = malloc(2 * sizeof(int));
	while (str[i])
	{
		while (str[i][j])
		{
			if (str[i][j] == '\'' || str[i][j] == '\"')
			{
				firstquote[0] = i;
				firstquote[1] = j;
				j = afterquotes(str, firstquote, pos);
				return (free(firstquote), j);
			}
			j++;
		}
		i++;
		j = 0;	
	}
	return (free(firstquote), 0);
}

/*int	checkpos(char *str, int firstquote, int pos)
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
}*/

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
			i++;
			while(str[i] && (str[i] != '\'' && str[i] != '\"'))
				i++;
			if (str[i] == '\'' || str[i] == '\"')
			{
				tab[quote] = i;
				quote++;
			}
			else if (!str[i])
				break;
		}
		i++;
	}
	return (tab);
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

char **sortquotes(char *str)
{
	int		i;
	int		j;
	int		k;
	int		len;
	char	**tab;
	int		*pos;

	i = 0;
	j = 0;
	k = 1;
	pos = quotespos(str);
	if (pos == NULL)
		return (NULL);
	len = countquotes(str);
	tab = malloc ((countquotes(str) + 1 ) * sizeof (char *));
	if (tab == NULL)
		return (NULL); 
	while (i < len)
	{
		if (str[pos[i]] == str[pos[k]])
		{
			tab[j] = ft_strduppos(str, pos[i], pos[k]);
			i = k + 1;
			k++;
			j++;
		}
		k++;
	}
	free(pos);
	while (j < len)
	{
		tab[j] = NULL;
		j++;
	}
	tab[j] = NULL;
	return(tab);
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
