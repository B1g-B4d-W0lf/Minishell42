/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:48:09 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/11 17:45:34 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	countredir(char **str)
{
	int	i;
	int	pos;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		pos = i;
		if ((str[i][0] == '<' || str[i][0] == '>') && insidequotes(str, pos) == 0)
			count++;
		i++;
	}
	return (count);
}

int countfiles(char **str, char c)
{
	int	i;
	int	pos;
	int	count;
	
	i = 0;
	count = 0;
	while(str[i])
	{
		pos = i;
		if (str[i][0] == c && insidequotes(str, pos) == 0)
			count++;
		i++;
	}
	return (count);
}

char **sortfiles(char **str, char c)
{
	int		i;
	int		j;
	int		pos;
	char	**files;

	i = 0;
	j = 0;
	files = malloc((countfiles(str, c) + 1) * sizeof(char *));
	if (files == NULL)
		return (NULL);
	while (str[i])
	{
		pos = i;
		if(str[i][0] == c && insidequotes(str, pos) == 0)
		{
			i++;
			files[j] = ft_strdup(str[i]);
			j++;
		}
		i++;
	}
	files[j] = NULL;
	return (files);
}

int	*sortredir(char **str)
{
	int	i;
	int	j;
	int	pos;
	int	*tabl;

	i = 0;
	j = -1;
	tabl = malloc(countredir(str) * sizeof(int));
	if (tabl == NULL)
		return (NULL);
	while (str[i])
	{
		pos = i;
		if (insidequotes(str, pos) == 0)
		{
			if (str[i][0] == '<' && !str[i][1])
				tabl[++j] = redir_left;
			else if (str[i][0] == '>' && !str[i][1])
				tabl[++j] = redir_right;
			else if (str[i][0] == '>' && str[i][1])
				tabl[++j] = redir_double_right;
			else if (str[i][0] == '<' && str[i][1])
				tabl[++j] = redir_double_left;
		}
		i++;
	}
	return (tabl);
}
