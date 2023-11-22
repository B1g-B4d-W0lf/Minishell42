/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:56:30 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/22 16:57:37 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	whilequote(char **str, int i)
{
	int	j;

	j = 0;
	while (str[i][j])
	{
		if (str[i][j] != '\"' && str[i][j] != '\'')
		{
			if (insidequotes(str, i, j) != 0)
				return (1);
		}
		j++;
	}
	return (0);
}

char	*execdupquotes(char *str, int start, int end, int ab)
{
	char	*line;
	int		i;

	i = -1;
	line = malloc((end - start + 2) * sizeof(char));
	if (!line)
		return (NULL);
	line[++i] = str[ab];
	while (start < end)
	{
		if (str[start] != str[ab])
		{
			line[++i] = str[start];
			start++;
		}
		else
			start++;
	}
	if (line[i] != str[ab])
		line[++i] = str[ab];
	line[++i] = '\0';
	return (line);
}

char	*ft_dupquotes(char *str, int start, int end)
{
	char	*tabl;
	int		ab;

	ab = start;
	if (isnospace(str, &start, &end))
		tabl = execdupquotes(str, start, end, ab);
	else
		tabl = ft_strduppos(str, start, end);
	return (tabl);
}

int	isnospace(char *str, int *i, int *j)
{
	int	ab;
	int	bc;

	ab = *i;
	bc = *j;
	if (*i > 0)
	{
		if (str[*i - 1] != ' ')
		{
			while (*i > 0 && str[*i - 1] != ' ')
				*i = *i - 1;
		}
	}
	if (str[*j + 1] && str[*j + 1] != ' ')
	{
		while (str[*j] && str[*j] != ' ')
			*j = *j + 1;
	}
	if (*i != ab || *j != bc)
		return (1);
	return (0);
}

int	isvaliddollar(char *str, int pos)
{
	if (str[pos] == '$')
	{
		if (pos > 0)
		{
			if (ft_isalnum(str[pos - 1]))
				return (1);
		}
		if (!str[pos + 1] || str[pos + 1] == ' ')
			return (1);
		return (0);
	}
	return (1);
}
