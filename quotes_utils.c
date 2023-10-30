/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:58:34 by wfreulon          #+#    #+#             */
/*   Updated: 2023/10/30 19:15:01 by wfreulon         ###   ########.fr       */
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
		if (!comparedoublepos(pos, firstquote, secondquote))
			return (free(secondquote), 0);
		else if (comparedoublepos(pos, firstquote, secondquote) 
			&& str[firstquote[0]][firstquote[1]] == '\'')
			return (free(secondquote), 1);
		else if (comparedoublepos(pos, firstquote, secondquote) 
			&& str[firstquote[0]][firstquote[1]] == '\"')
			return (free(secondquote), 2);
	}
	return (free(secondquote), 3);
}
