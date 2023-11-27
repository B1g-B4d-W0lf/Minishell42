/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:04:36 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/25 21:20:13 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freedoubletab(char **tabl)
{
	int		i;

	i = 0;
	while (tabl[i])
	{
		if (tabl[i])
			free(tabl[i]);
		i++;
	}
	free(tabl);
}

void	cleanleak(int len, t_mini *mini)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (mini->cmds[i].cmd)
			freedoubletab(mini->cmds[i].cmd);
		if (mini->cmds[i].path)
			free(mini->cmds[i].path);
		if (mini->cmds[i].redir_type)
			free(mini->cmds[i].redir_type);
		if (mini->cmds[i].input_file)
			freedoubletab(mini->cmds[i].input_file);
		if (mini->cmds[i].output_file)
			free(mini->cmds[i].output_file);
		if (mini->cmds[i].hd)
			free(mini->cmds[i].hd);
		i++;
	}
	free(mini->cmds);
	freedoubletab(mini->envp);
	free(mini->cmds);
}

int	freeints(int *firstquote, int *t, int *pos)
{
	int	i;

	i = t[2];
	if (pos)
		free(pos);
	if (t)
		free(t);
	if (firstquote)
		free(firstquote);
	return (i);
}

void	freetfill(t_fill *fill)
{
	if (fill->line)
		freedoubletab(fill->line);
	if (fill->quote)
		freedoubletab(fill->quote);
	if (fill->paths)
		freedoubletab(fill->paths);
	if (fill->spaced)
		free(fill->spaced);
	free (fill);
}