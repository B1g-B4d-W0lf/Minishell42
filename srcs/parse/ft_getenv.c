/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 21:16:55 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/11 20:30:53 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copyenv(char **envp, int i, int len)
{
	int		j;
	char	*var;
	
	j = 0;
	var = malloc((ft_strlen(envp[i]) - len) * sizeof(char));
	len++;
	if (!var)
		return (NULL);
	while (envp[i][len])
	{
		var[j] = envp[i][len];
		j++;
		len++;
	}
	var[j] = '\0';
	return (var);
}

char *ft_getenv(char *str, char **envp)
{
	int		i;
	int		len;
	char	*var;

	i = 0;
	len = ft_strlen(str);
	while (envp && envp[i])
	{
		if (!ft_strncmp(str, envp[i], len))
		{
			
			if (!envp[i][len] || !envp[i][len + 1])
				return (NULL);
			if (envp[i][len] == '=')
			{
				var = copyenv(envp, i, len);
				return (free (str), var);
			}
		}
		i++;
	}
	return(free(str), NULL);
}
