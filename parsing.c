/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 19:44:06 by wfreulon          #+#    #+#             */
/*   Updated: 2023/09/13 16:02:50 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//remplir la struct tmtc
t_cmd	*fillcmd(char *str, int nbr)
{
	t_cmd	*cmd;
	
	cmd = malloc(sizeof (t_cmd));
	if (!cmd)
		return (NULL);
	cmd->token = findtoken(str);
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
