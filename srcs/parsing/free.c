/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:48:19 by jehubert          #+#    #+#             */
/*   Updated: 2023/11/21 17:05:54 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_cmds(int i, t_mini *mini)
{
	int	k;

	k = -1;
	while (++k < i)
	{
		ft_clean_split(mini->cmds[k].cmd);
		ft_clean_split(mini->cmds[k].input_file);
		ft_clean_split(mini->cmds[k].output_file);
		free(mini->cmds[k].path);
		free(mini->cmds[k].redir_type);
		free(mini->cmds[k].hd);
	}
	free(mini->cmds);
}
