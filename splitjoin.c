/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitjoin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 20:41:10 by wfreulon          #+#    #+#             */
/*   Updated: 2023/09/26 16:20:08 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"
// prototype au cas ou, meme si tres incomplet pour le spacing

int	countingchar(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	while(str[i])
	{
		if(str[i] == c)
			count++;
		i++;
	}
	return (count);
}

char *splittojoin(char *str, char c)
{
	char 	**temp;
	char	*strbis;
	int		i;

	i = 0;
	temp = ft_split(str, c);
	while (temp[i])
	{
		temp[i] = ft_strjoin(temp[i]," c ")
		i++;
	}
	i = 0;
	while (temp[i])
	{
		strbis = ft_strjoin(temp[i], temp[i + 1]); //boucle pour ft join le split modifié
	}
	return (strbis);
}
char *spaceitbis(char *str)
{
	int		i;
	
	i = 0;
	if (findchar(str, '<'))
		str = splittojoin(str, '<');
	if (findchar(str, '>'))
		str = splittojoin(str, '>');
	if(findchar(str, '|'))
		str = splittojoin(str, '|');
	return(str);
}
