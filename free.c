/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:04:36 by wfreulon          #+#    #+#             */
/*   Updated: 2023/09/11 14:59:58 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//les doubles tableaux 4 ever
void	freedoubletab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
//nom de fonction prétentieux pour un programme avec 200 leaks
void	cleanleak(t_mini *mini)
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
			free(mini->cmds[i]);
			i++;
		}
		free(mini->cmds);
	}
}