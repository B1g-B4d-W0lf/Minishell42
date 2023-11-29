/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:43:49 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/29 17:43:50 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipex_error(int **pfd, t_mini *minsh)
{
	print_error("Error: pipe failed\n");
	if (pfd[1][0] > 0)
		close(pfd[1][0]);
	clear_double_tab_int(pfd, 2);
	free_t_mini(minsh);
	exit(1);
}
