/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:57:15 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/22 15:57:07 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execreplace(char *str, char **temp, char *expanded, int *t)
{
	int	l;
	int	k;

	l = -1;
	k = t[2];
	if (!isvaliddollar(str, t[0]) && (insidequotesstr(str, t[0]) == 2
			|| insidequotesstr(str, t[0]) == 0))
	{
		t[0] = t[0] + 1;
		if (str[t[0]] == '?')
			t[0] = t[0] + 1;
		else if (isdigit(str[t[0]]))
			t[0] = t[0] + 1;
		else if (str[t[0]] != '?' && !isdigit(str[t[0]]))
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

char	*end_expand(char **temp, char *str, int j)
{
	char	*expanded;

	temp[j] = NULL;
	if (j != 0)
	{
		expanded = malloc((ft_strlen(str) + totallen(temp) + 1) * sizeof(char));
		if (!expanded)
			return (NULL);
		seeknreplace(str, temp, expanded);
		freedoubletab(temp);
		return (free(str), expanded);
	}
	freedoubletab(temp);
	return (str);
}

void	execexpand(t_expand *e)
{
	extern int	g_status;

	if (e->str[e->i + 1] && e->str[e->i + 1] == '?')
	{
		e->tp[e->j] = ft_itoa(g_status);
		e->i = e->i + 2;
		e->j++;
	}
	else if (!e->str[e->i + 1]
		|| (e->str[e->i + 1] && isalnum(e->str[e->i + 1])))
	{
		e->i++;
		e->pos[0] = e->i;
		if (isdigit(e->str[e->i]))
			e->i++;
		else
		{
			while (e->str[e->i] && isalnum(e->str[e->i]))
				e->i++;
		}
		e->pos[1] = e->i - 1;
		e->tp[e->j] = fge(ft_strduppos(e->str, e->pos[0], e->pos[1]), e->env);
		e->j++;
	}
}

char	*expanding(char *str, char **envp)
{
	t_expand	exp;

	exp.i = 0;
	exp.j = 0;
	exp.str = str;
	exp.env = envp;
	if (!checkdollar(str))
		return (str);
	exp.tp = malloc((checkdollar(str) + 1) * sizeof(char *));
	if (exp.tp == NULL)
		return (NULL);
	while (str[exp.i])
	{
		if (!isvaliddollar(str, exp.i) && (insidequotesstr(str, exp.i) == 2
				|| insidequotesstr(str, exp.i) == 0))
			execexpand(&exp);
		if (str[exp.i])
			exp.i++;
	}
	return (end_expand(exp.tp, exp.str, exp.j));
}
