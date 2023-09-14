/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:34:51 by wfreulon          #+#    #+#             */
/*   Updated: 2023/09/12 16:38:02 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//pour le malloc de spaceit (taille + espaces)
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
			if	(((str[i] == '>' || str[i] == '<') && (str[i + 1] != ' ')) || str[i] != ' ')
			{
				count++;
				i++;
			}
		}
		else
			i++;
	}
	return (i + count);
}
void	addspace(int *i, int *j, char *spaced, char *str)
{
	spaced[*j] = ' ';
	*j = *j + 1;
	spaced[*j] = str[*i];
	*j = *j + 1;
	*i = *i + 1;	
}
//separer les token et les cmd par des espaces (pour split)
char	*spaceit(char *str)
{
	int		i;
	int		j;
	char	*spaced;

	i = 0;
	j = 0;
	spaced = malloc(symbolcount(str) * sizeof(char) + 1);
	if (!spaced)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == '|' || str[i] == '>' || str[i] == '<') && (str[i - 1] != ' '))
		{
			addspace(&i, &j, spaced, str);
			if (str[i] != ' ' && str[i] != '<' && str[i] != '>')
				addspace(&i, &j, spaced, str);
			if	((str[i] == '>' || str[i] == '<') && (str[i + 1] != ' '))
				addspace(&i, &j, spaced, str);
		}
		else 
		{
			spaced[j] = str[i];
			j++;
			i++;
		}
	}
	spaced[j] = '\0';
	return (spaced);
}
//trouver le token pr le renvoyer dans la struct pr exec
char	findtoken(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>' || str[i] == '$')
		{
			if (str[i + 1] == '<' || str[i + 1] == '>')
				return (str[i]);//return double redir how?
			return (str[i]);
		}
		i++;
	}
	return ('\0');
}
//bool pr trouver si il y a des pipes dans la line
int	ispipe(char *str)
{
	int	i;
	int	pipe;
	
	i = 0;
	pipe = 0;
	while (str[i])
	{
		if (str[i] == '|' && str[i + 1] != '|')
			pipe ++;
		i++;
	}
	return (pipe);
}
