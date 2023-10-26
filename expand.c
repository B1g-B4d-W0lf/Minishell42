/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:57:15 by wfreulon          #+#    #+#             */
/*   Updated: 2023/10/26 18:31:44 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//donne la taille du double tableau
int	sizeofdoubletab(char **tab)
{
	int	i;
	
	i = 0;
	while(tab[i])
		i++;
	return(i);
}
//y'as t'il une possible indication de variable hmm
int	checkdollar(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i][0] == '$')
			return (1);
		i++;
	}
	return (0);
}
//cherche la valeur de la variable et la remplace dans le tableau yay
char *seeknreplace(char *str)
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
char **expanding(char **str)
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
}
