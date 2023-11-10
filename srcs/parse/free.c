/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:04:36 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/09 19:17:52 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//les doubles tableaux 4 ever
void	freedoubletab(char **tabl)
{
	int		i;

	i = 0;
	while (tabl[i])
	{
		free(tabl[i]);
		i++;
	}
	free(tabl);
}
//nom de fonction prétentieux pour un programme avec 200 leaks
void	cleanleak(t_minish *mini)
{
	int	i;

	i = 0;
	if (mini->cmds)
	{
		while(mini->cmds[i])
		{
			if (mini->cmds[i]->cmd)
				freedoubletab(mini->cmds[i]->cmd);
			if (mini->cmds[i]->path)
				free(mini->cmds[i]->path);
			if (mini->cmds[i]->redirtype)
				free(mini->cmds[i]->redirtype);
			if (mini->cmds[i]->infile)
				free(mini->cmds[i]->infile);
			if (mini->cmds[i]->outfile)
				free(mini->cmds[i]->outfile);
			if (mini->cmds[i]->quote)
				freedoubletab(mini->cmds[i]->quote);
			free(mini->cmds[i]);
			i++;
		}
		freedoubletab(mini->paths);
		free(mini->cmds);
	}
}