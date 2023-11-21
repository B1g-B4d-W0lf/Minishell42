/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 19:45:34 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/20 18:19:30 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**realloc_envp(char **envp)
{
	int		i;
	int		j;
	char	**dup;

	i = 0;
	j = 0;
	dup = malloc((sizeofdoubletab(envp) + 1) * sizeof(char *));
	while (envp && envp[i])
	{
		dup[j] = ft_strdup(envp[i]);
		i++;
		j++;
	}
	dup[j] = NULL;
	return (dup);
}

char	**findpath(char **envp)
{
	int		i;
	char	**paths;
	char	*dup;

	i = 0;
	while (envp && envp[i])
	{
		if (!ft_strncmp("PATH=", envp[i], 5))
		{
			dup = ft_strdup(envp[i]);
			paths = ft_split(dup + 5, ':');
			free(dup);
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*whilenorm(char *str, char *s2, int i, int j)
{
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

int	isbuiltin(char *str)
{
	if (!strncmp(str, "echo", 4))
		return (1);
	else if (!strncmp(str, "cd", 2))
		return (1);
	else if (!strncmp(str, "pwd", 3))
		return (1);
	else if (!strncmp(str, "export", 6))
		return (1);
	else if (!strncmp(str, "unset", 5))
		return (1);
	else if (!strncmp(str, "env", 3))
		return (1);
	else if (!strncmp(str, "exit", 4))
		return (1);
	return (0);
}

char	*sendpath(char **str, char **paths)
{
	int		i;
	char	*pathtest;
	char	*dup;

	i = 0;
	pathtest = NULL;
	if (*str == NULL || isbuiltin(*str) || paths == NULL)
		return (NULL);
	if (findchar(*str, '/'))
	{
		*str = dupcmdslash(*str, &dup);
		return (dup);
	}
	while (paths[i])
	{
		pathtest = ft_sup_join(paths[i], '/', *str);
		if (access(pathtest, F_OK) == 0)
			return (free(pathtest), ft_strjoin(paths[i], "/"));
		free(pathtest);
		i++;
	}
	return (NULL);
}
