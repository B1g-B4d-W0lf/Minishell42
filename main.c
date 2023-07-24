/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:33:26 by wfreulon          #+#    #+#             */
/*   Updated: 2023/07/24 22:44:44 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	symbolcount(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if ((str[i] == '|' || str[i] == '>' || str[i] == '<') && (str[i - 1] != ' '))
		{
			count++;
			i++;
			if	((str[i] == '>' || str[i] == '<') && (str[i + 1] != ' '))
			{
				count++;
				i++;
			}
		}
		i++;
	}
	return (i + count);
}

char *spaceit(char *str)
{
	int		i;
	int		j;
	char	*spaced;

	i = 0;
	j = 0;
	spaced = malloc(symbolcount(str) * sizeof(char) + 1);
	while (str[i])
	{
		if ((str[i] == '|' || str[i] == '>' || str[i] == '<') && (str[i - 1] != ' '))
		{
			spaced[j] = ' ';
			j++;
			spaced[j] = str[i];
			j++;
			i++;
			if	((str[i] == '>' || str[i] == '<') && (str[i + 1] != ' '))
			{
				spaced[j] = str[i];
				j++;
				spaced[j] = ' ';
				j++;
				i++;
			}
		}
		spaced[j] = str[i];
		j++;
		i++;
	}
	return (spaced);
}

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
		mini.input = readline("minishell ➤ ");
		if (mini.input != NULL && *mini.input != '\0')
		{
			add_history(mini.input);
		}
		if (!ft_strncmp(mini.input, "exit", 4))
			mini.exit = 1;
		printf("%s\n", spaceit(mini.input));
	}
}
