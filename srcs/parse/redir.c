/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:48:09 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/14 21:36:16 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	countredir(char **str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i][0] == '<' || str[i][0] == '>')
			count++;
		i++;
	}
	return (count);
}

int countfiles(char **str, char c)
{
	int	i;
	int	count;
	
	i = 0;
	count = 0;
	while(str[i])
	{
		if (str[i][0] == c)
			count++;
		i++;
	}
	return (count);
}

char **sortfiles(char **str, char c)
{
	int		i;
	int		j;
	char	**files;

	i = 0;
	j = 0;
	files = malloc((countfiles(str, c) + 1) * sizeof(char *));
	if (files == NULL)
		return (NULL);
	while (str[i])
	{
		if(str[i][0] == c)
		{
			i++;
			if (str[i][0] == '\"' || str[i][0] == '\'' )
				files[j] = ft_strduppos(str[i], 1, ft_strlen(str[i]) - 2);
			else
				files[j] = ft_strdup(str[i]);
			j++;
		}
		i++;
	}
	files[j] = NULL;
	return (files);
}

int	*sortredir(char **str, int *hd)
{
	int	i;
	int	j;
	int	k;
	int	*tabl;

	i = 0;
	j = -1;
	k = 0;
	tabl = malloc(countredir(str) * sizeof(int));
	if (tabl == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i][0] == '<' && !str[i][1])
			tabl[++j] = redir_left;
		else if (str[i][0] == '>' && !str[i][1])
			tabl[++j] = redir_right;
		else if (str[i][0] == '>' && str[i][1])
			tabl[++j] = redir_double_right;
		else if (str[i][0] == '<' && str[i][1])
			tabl[++j] = redir_double_left;
		if (str[i + 1] && (str[i][0] == '<' || str[i][0] == '>'))
		{
			if (str[i + 1][0] == '\"' || str[i + 1][0] == '\'')
				hd[k] = 1;
			else
				hd[k] = 0;
			k++;
		}
		i++;
	}
	return (tabl);
}
