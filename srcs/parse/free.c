/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:04:36 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/22 20:09:56 by wfreulon         ###   ########.fr       */
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
		freedoubletab(mini->cmds[i].cmd);
		free(mini->cmds[i].path);
		free(mini->cmds[i].redir_type);
		free(mini->cmds[i].input_file);
		free(mini->cmds[i].output_file);
		free(mini->cmds[i].hd);
		i++;
	}
	free(mini->cmds);
	freedoubletab(mini->envp);
	free(mini->cmds);
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
