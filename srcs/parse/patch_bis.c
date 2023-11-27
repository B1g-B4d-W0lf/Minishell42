/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patch_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:58:54 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/27 17:59:58 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_to_null_cmd(t_cmd *cmd)
{
	cmd->hd = NULL;
	cmd->redir_type = NULL;
	cmd->redir = 0;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->redir_in = 0;
	cmd->redir_out = 0;
	cmd->cmd = NULL;
	cmd->path = NULL;
}

void	set_to_null_fill(t_fill *fill)
{
	fill->line = NULL;
	fill->paths = NULL;
	fill->quote = NULL;
	fill->spaced = NULL;
}

void	mallocerror(t_fill *fill, t_mini *mini)
{
	if (fill)
		freetfill(fill);
	if (mini->cmds)
		cleanleak(mini->nb_cmd, mini);
	exit (12);
}

int	mallocfailint(int *t, int *fq, int *pos)
{
	if (pos)
		free(pos);
	if (t)
		free(t);
	if (fq)
		free(fq);
	return (-1);
}
