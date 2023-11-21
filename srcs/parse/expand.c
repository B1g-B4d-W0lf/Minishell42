/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:57:15 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/20 21:22:42 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execreplace(char *str, char **temp, char *expanded, int *t)
{
	int	l;
	int	k;

	l = -1;
	k = t[2];
	if (str[t[0]] == '$' && (insidequotesstr(str, t[0]) == 2
			|| insidequotesstr(str, t[0]) == 0))
	{
		t[0] = t[0] + 1;
		if (str[t[0]] == '?')
			t[0] = t[0] + 1;
		if (isdigit(str[t[0]]))
			t[0] = t[0] + 1;
		else
		{
			while (str[t[0]] && ft_isalnum(str[t[0]]))
				t[0] = t[0] + 1;
		}
		while (temp[k] && temp[k][++l])
			expanded[++t[1]] = temp[k][l];
		t[2] = k + 1;
	}
	expanded[++t[1]] = str[t[0]];
	if (str[t[0]])
		t[0] = t[0] + 1;
}

void	seeknreplace(char *str, char **temp, char *expanded)
{
	int	*t;
	int	len;

	t = malloc(4 * sizeof(int));
	if (!t)
		return ;
	t[0] = 0;
	t[1] = -1;
	t[2] = 0;
	t[3] = -1;
	len = totallen(temp) + ft_strlen(str);
	while (str[t[0]])
		execreplace(str, temp, expanded, t);
	while (t[1] < len)
		expanded[++t[1]] = '\0';
	return (free(t));
}

char	*end_expand(char **temp, char *str)
{
	char	*expanded;

	expanded = malloc((ft_strlen(str) + totallen(temp) + 1) * sizeof(char));
	seeknreplace(str, temp, expanded);
	freedoubletab(temp);
	return (free(str), expanded);
}

char	*expanding(char *str, char **envp)
{
	int			i;
	extern int	g_status;
	int			pos[2];
	int			j;
	char		**temp;

	i = 0;
	j = 0;
	if (!checkdollar(str))
		return (str);
	temp = malloc((checkdollar(str) + 1) * sizeof(char *));
	if (temp == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && (insidequotesstr(str, i) == 2
				|| insidequotesstr(str, i) == 0))
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
		return (end_expand(temp, str));
	freedoubletab(temp);
	return (str);
}
