/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 19:44:06 by wfreulon          #+#    #+#             */
/*   Updated: 2023/07/29 19:47:16 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	symbolcount(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if ((str[i] == '|' || str[i] == '>' || str[i] == '<') && (str[i - 1] != ' '))
		{
			count++;
			i++;
			if	((str[i] == '>' || str[i] == '<') && (str[i + 1] != ' '))
			{
				count++;
				i++;
			}
		}
		i++;
	}
	return (i + count);
}

char	*spaceit(char *str)
{
	int		i;
	int		j;
	char	*spaced;

	i = 0;
	j = 0;
	spaced = malloc(symbolcount(str) * sizeof(char) + 1);
	while (str[i])
	{
		if ((str[i] == '|' || str[i] == '>' || str[i] == '<') && (str[i - 1] != ' '))
		{
			spaced[j] = ' ';
			j++;
			spaced[j] = str[i];
			j++;
			i++;
			if	((str[i] == '>' || str[i] == '<') && (str[i + 1] != ' '))
			{
				spaced[j] = str[i];
				j++;
				spaced[j] = ' ';
				j++;
				i++;
			}
		}
		spaced[j] = str[i];
		j++;
		i++;
	}
	return (spaced);
}
