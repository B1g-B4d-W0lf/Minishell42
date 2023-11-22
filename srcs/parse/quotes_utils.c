/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:58:34 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/22 19:55:11 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	whilenofq(char **str, int *pos, int *fq, int *t)
{
	if (str[t[0]][t[1]] == '\'' || str[t[0]][t[1]] == '\"')
	{
		fq[0] = t[0];
		fq[1] = t[1];
		t[2] = afterquotes(str, fq, pos[0], pos[1]);
		if (t[2] != 0)
			return (t[2]);
		t[0] = fq[0];
		t[1] = fq[1];
	}
	t[1]++;
	return (0);
}

int	countquotes(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			count++;
		i++;
	}
	return (count);
}

int	comparedoublepos(int a, int b, int *firstquote, int *secondquote)
{
	if (a >= firstquote[0])
	{
		if (a == firstquote[0] && b < firstquote[1])
			return (0);
		else if (a == secondquote[0] && b < secondquote[1])
			return (1);
		else if (a <= secondquote[0])
			return (1);
	}
	return (0);
}

void	whilenosq(char **str, int *fq, int *i, int *j)
{
	while (str[*i][*j] && str[*i][*j] != str[fq[0]][fq[1]])
		*j = *j + 1;
	if (str[*i][*j] == str[fq[0]][fq[1]])
		return ;
	*i = *i + 1;
	*j = 0;
}

int	afterquotes(char **str, int *fq, int a, int b)
{
	int	*sq;
	int	i;
	int	j;

	sq = malloc(2 * sizeof(int));
	if (!sq)
		return (-1);
	i = fq[0];
	j = fq[1] + 1;
	while (str[i] && str[i][j] != str[fq[0]][fq[1]])
		whilenosq(str, fq, &i, &j);
	if (str[i] && str[i][j] == str[fq[0]][fq[1]])
	{
		sq[0] = i;
		sq[1] = j;
		if (comparedoublepos(a, b, fq, sq) && str[fq[0]][fq[1]] == '\'')
			return (free(sq), 1);
		else if (comparedoublepos(a, b, fq, sq) && str[fq[0]][fq[1]] == '\"')
			return (free(sq), 2);
	}
	else if (!str[i])
		return (free(sq), 3);
	fq[0] = i;
	fq[1] = j;
	return (free(sq), 0);
}
