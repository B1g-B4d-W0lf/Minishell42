/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 19:44:06 by wfreulon          #+#    #+#             */
/*   Updated: 2023/09/11 17:33:21 by wfreulon         ###   ########.fr       */
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
	if (!spaced)
		return (NULL);
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
	spaced[j] = '\0';
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

t_cmd	*fillcmd(char *str, int nbr)
{
	t_cmd	*cmd;
	
	cmd = malloc(sizeof (t_cmd));
	if (!cmd)
		return (NULL);
	cmd->token = findtoken(str);
	cmd->cmd = ft_split(str, ' ');
	cmd->nbr = nbr;
	return (cmd);
}
//separer et stocker les infos de la ligne dans la struct
t_mini	parse(t_mini *mini)
{
	char	*spaced;
	char	**piped;
	t_cmd	**cmd;
	int		nbr = 0;
	int		i = 0;
	
	spaced = spaceit(mini->input);
	cmd = NULL;
	if (ispipe(spaced) == 0)
	{
		cmd = malloc(sizeof (t_cmd));
		*cmd = fillcmd(spaced, nbr);
		mini->cmds = cmd;
	}
	else if (ispipe(spaced))
	{
		cmd = malloc(sizeof (t_cmd) * ispipe(spaced));
		piped = ft_split(spaced, '|');
		while (piped[i])
		{
			cmd[nbr] = fillcmd(piped[i], nbr);
			nbr++;
			i++;
		}
		freedoubletab(piped);
		mini->cmds = cmd;
	}
	free(spaced);
	return (*mini);
}
