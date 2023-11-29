/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:38:53 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/29 17:38:56 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_dir(t_mini *mini, int pos)
{
	struct stat	s;
	char		*str;

	if (stat(mini->cmds[pos].cmd[0], &s) == 0)
	{
		if (s.st_mode & S_IFDIR)
		{
			str = ft_strjoin(mini->cmds[pos].cmd[0], ": is a directory\n");
			print_error(str);
			free(str);
			free_t_mini(mini);
			exit(126);
		}
	}
	return (1);
}
