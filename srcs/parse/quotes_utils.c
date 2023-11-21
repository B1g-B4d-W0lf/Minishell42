/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:58:34 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/20 17:45:59 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	comparepos(int pos, int firstquote, int secondquote)
{
	if (pos > firstquote && pos < secondquote)
		return (1);
	return (0);
}

int	afterquotes(char **str, int firstquote, int pos, int *i)
{
	int	secondquote;

	while (str[*i] && str[*i][0] != str[firstquote][0])
	{
		if (str[*i][0] == str[firstquote][0])
			break ;
		*i = *i + 1;
	}
	if (str[*i] && str[*i][0] == str[firstquote][0])
	{
		secondquote = *i;
		if (comparepos(pos, firstquote, secondquote)
			&& str[firstquote][0] == '\'')
			return (1);
		else if (comparepos(pos, firstquote, secondquote)
			&& str[firstquote][0] == '\"')
			return (2);
	}
	else if (!str[*i])
		return (3);
	return (0);
}
