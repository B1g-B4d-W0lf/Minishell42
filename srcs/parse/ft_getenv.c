/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 21:16:55 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/10 23:22:14 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_getenv(char *str, char **envp)
{
	int		i;
	int		j;
	int		len;
	char	*var;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	while (envp && envp[i])
	{
		if (!ft_strncmp(str, envp[i], len))
		{
			
			if (!envp[i][len] || !envp[i][len + 1])
				return (NULL);
			if (envp[i][len] == '=')
			{
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
		}
		i++;
	}
	return(NULL);
}