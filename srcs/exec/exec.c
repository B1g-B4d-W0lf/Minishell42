/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 02:06:19 by alex              #+#    #+#             */
/*   Updated: 2023/07/30 16:01:07 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(t_mini *minsh)
{
	int	*pid;	

	pid = malloc(sizeof(int) * minsh->nb_cmd);
	pipex(minsh, pid);
	free(pid);
}
