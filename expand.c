/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:57:15 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/08 22:57:38 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//y'as t'il une possible indication de variable hmm
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

char *seeknreplace(char *str, char **temp, char *expanded)
{
	int	i;
	int	j;
	int	k;
	int	l;
	int	len;

	i = 0;
	j = 0;
	k = 0;
	l = 0;
	len = totallen(temp) + ft_strlen(str) + 1;
	while (str[i])
	{
		if (str[i] == '$' && (insidequotesstr(str, i) == 2 || insidequotesstr(str, i) == 0))
		{
			while (str[i] && str[i] != ' ' && str[i] != '\"')
				i++;
			while (temp[k] && temp[k][l])
			{
				expanded[j] = temp[k][l];
				l++;
				j++; 
			}
			k++;
		}
		expanded[j] = str[i];
		if (str[i])
			i++;
		j++;
	}
	while (j < len)
	{
		expanded[j] = '\0';
		j++;
	}
	return (expanded);
}

char *expanding(char *str)
{
	int		i;
	int		pos[2];
	int		j;
	char	**temp;
	char	*expanded;
	
	i = 0;
	j = 0;
	if (!checkdollar(str))
		return (str);
	temp = malloc((checkdollar(str) + 1) * sizeof(char *));
	if (temp == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && (insidequotesstr(str, i) == 2 || insidequotesstr(str, i) == 0))
		{
			pos[0] = i;
			while (str[i] && str[i] != ' ' && str[i] != '\"')//cas $., $8, $a  règle variable
				i++;
			pos[1] = i;
			temp[j] = getenv(ft_strduppos(str, pos[0], pos[1]));
			j++;
		}
		if (str[i])
			i++;
	}
	temp[j] = NULL;
	expanded = malloc((ft_strlen(str) + totallen(temp) + 1) * sizeof(char));
	expanded = seeknreplace(str, temp, expanded);
	freedoubletab(temp);
	return (expanded);
}
//cherche la valeur de la variable et la remplace dans le tableau yay
/*char *seeknreplacedoubletab(char *str)
{
	char *value;
	char *temp;
	int		i;
	
	i = 0;
	temp = getenv(str + 1);
	if (temp == NULL)
		return (free(str), NULL);
	value = malloc((ft_strlen(temp) + 1) * sizeof (char));
	while (temp[i])
	{
		value[i] = temp[i];
		i++;
	}
	value[i] = '\0';
	return (value);
}
//faut étendre ses horizons (trouvé si y'as une variable et la remplacer)
char **expandingdoubletab(char **str)
{
	int		i;
	int		j;
	char 	**temp;

	i = 0;
	j = 0;
	if (!checkdollar(str))
		return (str);
	temp = malloc((sizeofdoubletab(str) + 1) * sizeof (char *));	
	while (str[i])
	{
		if (str[i][0] == '$')
		{
			str[i] = seeknreplace(str[i]);
		}
		if (str[i] != NULL)
		{
			temp[j] = str[i];
			j++;
		}
		i++;
	}
	free(str);
	while (j != i)
	{
		temp[j] = NULL;
		j++;
	}
	temp[j] = NULL;
	return (temp);
}*/
