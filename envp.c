/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 19:45:34 by wfreulon          #+#    #+#             */
/*   Updated: 2023/10/25 18:22:34 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*ft_sup_join(char *s1, char c, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (0);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	str = malloc(((i + j) + 2) * sizeof (char));
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = c;
	i++;
	str = whilenorm(str, s2, i, j);
	return (str);
}

char *sendpath(char *str, char **paths)
{
	int		i;
	char	*pathtest;
	char	*dup;
	
	i = 0;
	pathtest = NULL;
	if (findchar(str, '/'))
	{
		dup = ft_strdup(str);
		return (dup);
	}
	while(paths[i])
	{
		pathtest = ft_sup_join(paths[i], '/', str);
		if (access(pathtest, F_OK) == 0)
			return (pathtest);
		free(pathtest);
		i++;
	}
	return (NULL);
}
