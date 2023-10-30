/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:48:09 by wfreulon          #+#    #+#             */
/*   Updated: 2023/10/30 18:57:22 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	countredir(char **str)
{
	int	i;
	int	j;
	int	*pos;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	pos = malloc(2 * sizeof(int));
	if (pos == NULL)
		return(0);
	while (str[i])
	{
		pos[0] = i;
		pos[1] = j;
		if ((str[i][j] == '<' || str[i][j] == '>') && insidequotes(str, pos) == 0)
			count++;
		i++;
	}
	free(pos);
	return (count);
}

int countfiles(char **str, char c)
{
	int	i;
	int	j;
	int	*pos;
	int	count;
	
	i = 0;
	j = 0;
	count = 0;
	pos = malloc(2 * sizeof(int));
	if (pos == NULL)
		return(0);
	while(str[i])
	{
		pos[0] = i;
		pos[1] = j;
		if (str[i][j] == c && insidequotes(str, pos) == 0)
			count++;
		i++;
	}
	free(pos);
	return (count);
}

char **sortfiles(char **str, char c)
{
	int		i;
	int		j;
	int		k;
	int		*pos;
	char	**files;

	i = 0;
	j = 0;
	k = 0;
	pos = malloc(2 * sizeof(int));
	if (pos== NULL)
		return(NULL);
	files = malloc((countfiles(str, c) + 1) * sizeof(char *));
	if (files == NULL)
		return (NULL);
	while (str[i])
	{
		pos[0] = i;
		pos[1] = j;
		if(str[i][j] == c && insidequotes(str, pos) == 0)
		{
			printf("ça rentre\n");
			i++;
			files[k] = ft_strdup(str[i]);
			k++;
		}
		i++;
	}
	free(pos);
	files[k] = NULL;
	return (files);
}

int	*sortredir(char **str)
{
	int	i;
	int	j;
	int	*pos;
	int	*tab;

	i = 0;
	pos = malloc(2 * sizeof(int));
	if (pos == NULL)
		return (NULL);
	j = -1;
	tab = malloc(countredir(str) * sizeof(int));
	if (tab == NULL)
		return (NULL);
	while (str[i])
	{
		pos[0] = i;
		pos[1] = 0;
		if (insidequotes(str, pos) == 0)
		{
			if (str[i][0] == '<' && !str[i][1])
				tab[++j] = 1;
			else if (str[i][0] == '>' && !str[i][1])
				tab[++j] = 2;
			else if (str[i][0] == '>' && str[i][1])
				tab[++j] = 3;
			else if (str[i][0] == '<' && str[i][1])
				tab[++j] = 4;
		}
		i++;
	}
	free(pos);
	return (tab);
}
