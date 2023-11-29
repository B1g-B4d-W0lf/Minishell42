/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 04:30:44 by alex              #+#    #+#             */
/*   Updated: 2023/11/29 17:46:33 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_mini *minsh, int position)
{
	char	*s;

	(void)position;
	s = malloc(sizeof(char) * (PATH_MAX + 1));
	if (s == NULL)
	{
		free_t_mini(minsh);
		exit(1);
	}
	getcwd(s, PATH_MAX);
	s[PATH_MAX] = '\0';
	secure_printf(minsh, position, s, 1);
	free(s);
	free_t_mini(minsh);
	exit(0);
}
