/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:33:26 by wfreulon          #+#    #+#             */
/*   Updated: 2023/07/22 19:21:39 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**findpath(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (envp && envp[i])
	{
		if (!ft_strncmp("PATH", envp[i], 4))
		{
			paths = ft_split(envp[i] + 5, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	
	(void)argc;
	(void)argv;
	mini.paths = findpath(envp);
	mini.exit = 0;
	while (mini.exit == 0)
	{
		ft_putstr_fd("minishell ➤", 0);
		mini.input = get_next_line(0);
		if (!ft_strncmp(mini.input, "exit", 4))
			mini.exit = 1;
	}
}