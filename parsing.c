/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 19:44:06 by wfreulon          #+#    #+#             */
/*   Updated: 2023/09/28 22:03:33 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//trouver si une string contient un char donné
int	findchar(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
//remplir la struct tmtc
t_cmd	*fillcmd(char *str, int nbr)
{
	t_cmd	*cmd;
	char	*temp;
	
	temp = findtoken(str);
	cmd = malloc(sizeof (t_cmd));
	if (!cmd)
		return (NULL);
	cmd->token = ft_split(temp, ' ');
	free(temp);
	cmd->cmd = expanding(ft_split(str, ' '));
	cmd->nbr = nbr;
	cmd->path = NULL;
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
	if (insidequotes(spaced, 5))
		ft_printf("oui c'est entre quotes ?????\n");
	if (ispipe(spaced) == 0)
	{
		cmd = malloc(sizeof (t_cmd) * 2);
		*cmd = fillcmd(spaced, nbr);
		mini->cmds = cmd;
		mini->cmds[1] = NULL;
	}
	else if (ispipe(spaced))
	{
		cmd = malloc(sizeof (t_cmd) * (ispipe(spaced) + 1));
		piped = ft_split(spaced, '|');
		while (piped[i])
		{	
			cmd[nbr] = fillcmd(piped[i], nbr);
			nbr++;
			i++;
		}
		freedoubletab(piped);
		mini->cmds = cmd;
		mini->cmds[nbr] = NULL;
	}
	free(spaced);
	return (*mini);
}
