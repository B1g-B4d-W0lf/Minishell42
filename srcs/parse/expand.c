/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:57:15 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/18 21:42:47 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void seeknreplace(char *str, char **temp, char *expanded)
{
	int	i;
	int	j;
	int	k;
	int	l;
	int	len;

	i = 0;
	j = 0;
	k = 0;
	l = 0;
	len = totallen(temp) + ft_strlen(str) + 1;
	while (str[i])
	{
		if (str[i] == '$' && (insidequotesstr(str, i) == 2 || insidequotesstr(str, i) == 0))
		{
			i++;
			if (str[i] == '?')
				i++;
			if (isdigit(str[i]))
				i++;
			else
			{
				while (str[i] && ft_isalnum(str[i]))
					i++;
			}
			while (temp[k] && temp[k][l])
			{
				expanded[j] = temp[k][l];
				l++;
				j++; 
			}
			k++;
		}
		expanded[j] = str[i];
		if (str[i])
			i++;
		j++;
	}
	while (j < len)
	{
		expanded[j] = '\0';
		j++;
	}
	return ;
}

char *expanding(char *str, char **envp)
{
	int			i;
	extern int	g_status;
	int			pos[2];
	int			j;
	char		**temp;
	char		*expanded;
	
	i = 0;
	j = 0;
	if (!checkdollar(str))
		return (str);
	temp = malloc((checkdollar(str) + 1) * sizeof(char *));
	if (temp == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && (insidequotesstr(str, i) == 2 || insidequotesstr(str, i) == 0))
		{
			if (str[i + 1] && str[i + 1] == '?' 
			&& (!str[i + 2] || str[i + 2] == ' ' || str[i + 2] == '\"'))
			{
				temp[j] = ft_itoa(g_status);
				while (str[i] && str[i] != ' ' && str[i] != '\"')
					i++;
				j++;
			}
			else if (!str[i + 1] || (str[i + 1] && isalnum(str[i + 1])))
			{
				i++;
				pos[0] = i;
				if (isdigit(str[i]))
					i++;
				else 
				{
					while (str[i] && isalnum(str[i]))
						i++;
				}
				pos[1] = i;
				temp[j] = ft_getenv(ft_strduppos(str, pos[0], pos[1] - 1), envp);
				j++;
			}
		}
		if (str[i])
			i++;
	}
	temp[j] = NULL;
	if (j != 0)
	{
		expanded = malloc((ft_strlen(str) + totallen(temp) + 1) * sizeof(char));
		seeknreplace(str, temp, expanded);
		freedoubletab(temp);
		return (free(str), expanded);
	}
	freedoubletab(temp);
	return (str);
}
