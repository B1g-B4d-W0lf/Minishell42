/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:34:51 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/11 22:14:19 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//pour le malloc de spaceit (taille + espaces)
int	symbolcount(char *str)
{
	int	i;
	int	count;

	i = 1;
	count = 0;
	if (((str[0] == '<' || str[0] == '>')
	&& (str[1] != '<' || str[1] != '>')) || (str[0] == '\'' || str[0] == '\"'))
		count++;
	while (str[i])
	{
		if ((str[i] == '|' || str[i] == '>' || str[i] == '<'
		|| str[i] == '\'' || str[i] == '\"'))
		{
			count = count + 2;
			i++;
			if	(str[i] == '>' || str[i] == '<')
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

void execspaceit(int *i, int *j, char *spaced, char *str)
{
	if ((str[*i] == '|' || str[*i] == '>' || str[*i] == '<'
	|| str[*i] == '\"' || str[*i] == '\''))
	{
		addspace(i, j, spaced, str);
		if (str[*i] && str[*i] != '<' && str[*i] != '>')
			addspace(i, j, spaced, str);
		if	(str[*i] && (str[*i] == '>' || str[*i] == '<') 
			&& (str[*i - 1] == '<' || str[*i - 1] == '>'))
		{
			spaced[*j] = str[*i];
			*j = *j + 1;
			spaced[*j] = ' ';
			*i = *i + 1;
			*j = *j + 1;
		}
	}
	else if ((str[*i] == '|' || str[*i] == '>' || str[*i] == '<'
	|| str[*i] == '\"' || str[*i] == '\'') && str[*i + 1] != '<'
	&& str[*i + 1] != '>')
	{
		*i = *i + 1;
		addspace(i, j, spaced, str);
	}
	else 
	{
		spaced[*j] = str[*i];
		*j = *j + 1;
		*i = *i + 1;
	}
	return ;
}
//separer les token et les cmd par des espaces (pour split)
char	*spaceit(char *str)
{
	int		i;
	int		j;
	char	*spaced;

	i = 1;
	j = 0;
	spaced = malloc((symbolcount(str) + 1) * sizeof(char));
	if (!spaced)
		return (NULL);
	spaced[j] = str[0];
	j++;
	if (((str[0] == '<' || str[0] == '>') || (str[0] == '\'' || str[0] == '\"')))
	{
		if ((str[0] == '<' || str[0] == '>') && (str[1] == '<' || str[1] == '>'))
		{
			spaced[j] = str[1];
			j++;
			i++;
			addspace(&i, &j, spaced, str);
		}
		else
			addspace(&i, &j, spaced, str);
	}
	while (str[i])
	{
		execspaceit(&i, &j, spaced, str);
	}
	spaced[j] = '\0';
	return (free(str), spaced);
} 
