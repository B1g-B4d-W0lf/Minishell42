/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitjoin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 20:41:10 by wfreulon          #+#    #+#             */
/*   Updated: 2023/10/26 17:45:43 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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
char	*whilenormbis(char *str, char *s2, int i, int j)
{
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

char	*ft_space_join(char *s1, char c, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (0);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	str = malloc(((i + j) + 4) * sizeof (char));
	if (str == NULL)
		return (NULL);
	j = 0;
	str = ft_strdup(s1);
	i++;
	str[i] = ' ';
	i++;
	str[i] = c;
	i++;
	str[i] = ' ';
	i++;
	free(s1);
	str = whilenormbis(str, s2, i, j);
	return (str);
}

char *splittojoin(char *str, char c)
{
	char 	**temp;
	char	*strbis;
	int		i;

	i = 1;
	temp = ft_split(str, c);
	strbis = temp[0];
	while (temp[i])
	{
		strbis = ft_space_join(strbis, c, temp[i]);
		i++;
	}
	freedoubletab(temp);
	return (strbis);
}
char *spaceitbis(char *str)
{

	if (findchar(str, '<'))
		str = splittojoin(str, '<');
	if (findchar(str, '>'))
		str = splittojoin(str, '>');
	if (findchar(str, '|'))
		str = splittojoin(str, '|');
	if (findchar(str, '\"'))
		str = splittojoin(str, '\"');
	if (findchar(str, '\''))
		str = splittojoin(str, '\'');
	return(str);
}
