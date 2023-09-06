/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 19:44:06 by wfreulon          #+#    #+#             */
/*   Updated: 2023/09/06 21:31:20 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//pour le malloc de spaceit (taille + espaces)
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
//separer les token et les cmd par des espaces (pour split)
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
//trouver le token pr le renvoyer dans la struct pr exec
char	findtoken(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>' || str[i] == '$')
		{
			if (str[i + 1] == '<' || str[i + 1] == '>')
				return (str[i]);//return double redir how?
			return (str[i]);
		}
		i++;
	}
	return ('\0');
}
//bool pr trouver si il y a des pipes dans la line
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
//separer et stocker les infos de la ligne dans la struct
void	parse(t_mini *mini)
{
	char	*spaced;
	char	**piped;
	t_cmd	*cmd = NULL;
	int		nbr = 1;
	int		i = 0;
	
	spaced = spaceit(mini->input);
	if (ispipe(spaced) == 0)
	{
		cmd[nbr].token = findtoken(spaced);
		cmd[nbr].cmd = ft_split(spaced, ' ');
		cmd[nbr].nbr = nbr;
		mini->cmds = &cmd[nbr];
	}
	else if (ispipe(spaced))
	{
		piped = ft_split(spaced, '|');
		while (piped[i])
		{
			cmd[nbr].token = findtoken(piped[i]);
			cmd[nbr].cmd = ft_split(piped[i], ' ');
			cmd[nbr].nbr = nbr;
			nbr++;
			i++;
		}
		mini->cmds = cmd;
	}
	return ;
}
