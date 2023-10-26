/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:48:09 by wfreulon          #+#    #+#             */
/*   Updated: 2023/10/26 16:09:16 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	countredir(char **str)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (str[i])
	{
		if (str[i][j] == '<' || str[i][j] == '>')
			count++;
		i++;
	}
	return (count);
}

int countfiles(char **str, char c)
{
	int	i;
	int	j;
	int	count;
	
	i = 0;
	j = 0;
	count = 0;
	while(str[i])
	{
		if (str[i][j] == c )
			count++;
		i++;
	}
	return (count);
}

char **sortfiles(char **str, char c)
{
	int		i;
	int		j;
	int		k;
	char	**files;

	i = 0;
	j = 0;
	k = 0;
	files = malloc((countfiles(str, c) + 1) * sizeof(char *));
	while (str[i])
	{
		if(str[i][j] == c )
		{
			i++;
			files[k] = ft_strdup(str[i]);
			k++;
		}
		i++;
	}
	files[k] = NULL;
	return (files);
}

int	*sortredir(char **str)
{
	int	i;
	int	j;
	int	k;
	int	*tab;

	i = 0;
	j = 0;
	k = -1;
	tab = malloc(countredir(str) * sizeof(int));
	while (str[i])
	{
		if (str[i][j] == '<' && !str[i][j + 1])
			tab[++k] = 1;
		else if (str[i][j] == '>' && !str[i][j + 1])
			tab[++k] = 2;
		else if (str[i][j] == '>' && str[i][j + 1])
			tab[++k] = 3;
		else if (str[i][j] == '<' && str[i][j + 1])
			tab[++k] = 4;
		i++;
	}
	return (tab);
}
