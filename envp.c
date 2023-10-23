/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 19:45:34 by wfreulon          #+#    #+#             */
/*   Updated: 2023/10/21 23:22:30 by wfreulon         ###   ########.fr       */
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
char	*whilenorm(char *str, char *s2, int *tab)
{
	while (s2[tab[3]])
	{
		str[tab[2] + tab[3]] = s2[tab[3]];
		tab[3]++;
	}
	str[tab[2] + tab[3]] = '\0';
	return (str);
}

char	*ft_sup_join(char *s1, char c, char *s2)
{
	char	*str;
	int		tab[5];

	if (!s1 || !s2)
		return (0);
	tab[0] = ft_strlen((char *) s1);
	tab[1] = ft_strlen((char *) s2);
	str = malloc(((tab[0] + tab[1]) + 2) * sizeof (char));
	if (str == NULL)
		return (NULL);
	tab[2] = 0;
	tab[3] = 0;
	while (s1[tab[2]])
	{
		str[tab[2]] = s1[tab[2]];
		tab[2]++;
	}
	str[tab[2]] = c;
	tab[2]++;
	str = whilenorm(str, s2, tab);
	free(s1);
	return (str);
}

char *sendpath(char *str, char **paths)
{
	int		i;
	char	*pathtest;
	
	i = 0;
	pathtest = NULL;
	while(paths[i])
	{
		pathtest = ft_sup_join(paths[i], '/', str);
		if (access(pathtest, F_OK) == 0)
			return (pathtest);
		i++;
	}
	free(pathtest);
	return (NULL);
}
