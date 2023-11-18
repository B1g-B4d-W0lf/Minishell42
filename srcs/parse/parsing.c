/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 19:44:06 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/18 20:23:02 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fillcmd(char *str, char **envp, t_cmd *cmd)
{
	char	**line;
	char	**quote;
	char	**paths;
	char	*spaced;
	
	paths = findpath(envp);
	spaced = expanding(str, envp);
	quote = sortquotes(spaced);
	spaced = spaceit(spaced);
	line = ft_split(spaced, ' ');
	cmd->hd = malloc(countredir(line) * sizeof(int));	
	cmd->redir_type = sortredir(line, cmd->hd);
	if (!(line = addquoted(line, quote)))
	{
		freecreations(spaced, line, quote, paths);
		return (-1);
	}
	cmd->redir = countredir(line);
	cmd->input_file = sortfiles(line, '<');
	cmd->output_file = sortfiles(line, '>');
	cmd->redir_in = countfiles(line, '<');
	cmd->redir_out = countfiles(line, '>');
	cmd->cmd = findcmd(line);
	if (cmd->cmd)
		cmd->path = sendpath(&cmd->cmd[0], paths);
	else if (!cmd->cmd)
		cmd->path = NULL;
	freecreations(spaced, line, quote, paths);
	return (0);
}

int	parse(t_mini *mini, char *line)
{
	char	**piped;
	int		nbr = 0;
	int		i = 0;
	
	if (checklineerr(line))
		return (-1);
	if (ispipe(line) == 0)
	{
		mini->cmds = malloc(sizeof (t_fill) * 2);
		if (fillcmd(ft_strdup(line), mini->envp, &mini->cmds[0]) != 0)
		{
			free (mini->cmds);
			return (-1);
		}
		return (1);
	}
	else if (ispipe(line))
	{
		mini->cmds = malloc(sizeof (t_fill) * (ispipe(line) + 2));
		piped = ft_split(line, '|');
		while (piped[i])
		{	
			if (fillcmd(piped[i], mini->envp, &mini->cmds[nbr]) != 0)
			{
				free (mini->cmds);
				return (-1);
			}
			nbr++;
			i++;
		}
		freedoubletab(piped);
		return(ispipe(line) + 1);
	}
	return (-1);
}
