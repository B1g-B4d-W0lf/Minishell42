/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:04:36 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/18 20:19:18 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	freecreations(char *str, char **line, char **quote, char **paths)
{
	if (line)
		freedoubletab(line);
	if (quote)
		freedoubletab(quote);
	if (paths)
		freedoubletab(paths);
	free(str);	
}