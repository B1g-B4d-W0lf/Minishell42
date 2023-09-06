/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 19:44:06 by wfreulon          #+#    #+#             */
/*   Updated: 2023/09/06 00:44:48 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	symbolcount(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if ((str[i] == '|' || str[i] == '>' || str[i] == '<') && (str[i - 1] != ' '))
		{
			count++;
			i++;
			if	((str[i] == '>' || str[i] == '<') && (str[i + 1] != ' '))
			{
				count++;
				i++;
			}
		}
		i++;
	}
	return (i + count);
}

char	*spaceit(char *str)
{
	int		i;
	int		j;
	char	*spaced;

	i = 0;
	j = 0;
	spaced = malloc(symbolcount(str) * sizeof(char) + 1);
	while (str[i])
	{
		if ((str[i] == '|' || str[i] == '>' || str[i] == '<') && (str[i - 1] != ' '))
		{
			spaced[j] = ' ';
			j++;
			spaced[j] = str[i];
			j++;
			i++;
			if	((str[i] == '>' || str[i] == '<') && (str[i + 1] != ' '))
			{
				spaced[j] = str[i];
				j++;
				spaced[j] = ' ';
				j++;
				i++;
			}
		}
		spaced[j] = str[i];
		j++;
		i++;
	}
	return (spaced);
}

char	findtoken(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>' || str[i] == '$')
		{
			if (str[i + 1] == '<' || str[i + 1] == '>')
				return (str[i]);
			return (str[i]);
		}
	}
	return ('\0');
}

int	ispipe(char *str)
{
	int	i;
	int	pipe;
	
	i = 0;
	pipe = 0;
	while (str[i])
	{
		if (str[i] == '|' && str[i + 1] != '|')
			pipe ++;
		i++;
	}
	return (pipe);
}

void	parse(t_mini *mini)
{
	char	*spaced;
	t_cmd	cmd;
	
	spaced = spaceit(mini->input);
	if (ispipe(spaced) == 0)
	{
		cmd.token = findtoken(spaced);
		cmd.cmd = ft_split(spaced, ' ');
		mini->cmds = &cmd;
	}
	else if (ispipe(spaced))
	{
		
	}
	return ;
}