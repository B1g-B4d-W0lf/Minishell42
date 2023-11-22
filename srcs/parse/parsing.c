/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 19:44:06 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/22 01:21:43 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execfillcmd(t_cmd *cmd, char **paths, char **line)
{
	cmd->hd = malloc(countredir(line) * sizeof(int));
	if (!cmd->hd)
		return ;
	cmd->redir_type = sortredir(line, cmd->hd);
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
}

int	fillcmd(char *str, char **envp, t_cmd *cmd)
{
	char	**line;
	char	**quote;
	char	**paths;
	char	*spaced;

	paths = findpath(envp);
	spaced = expanding(str, envp);
	quote = malloc((countquotes(spaced) + 1) * sizeof (char *));
	if (quote == NULL)
		return (freecreations(spaced, NULL, NULL, paths), -1);
	quote = sortquotes(spaced, quote);
	spaced = spaceit(spaced);
	line = ft_split(spaced, ' ');
	line = addquoted(line, quote);
	if (!line)
	{
		freecreations(spaced, line, quote, paths);
		return (printf("syntax error\n"), -1);
	}
	execfillcmd(cmd, paths, line);
	freecreations(spaced, line, quote, paths);
	return (0);
}

int	nopipeexec(t_mini *mini, char *line)
{
	mini->cmds = malloc(sizeof (t_cmd) * 2);
	if (!mini->cmds)
		exit (12);
	if (fillcmd(ft_strdup(line), mini->envp, &mini->cmds[0]) != 0)
	{
		free (mini->cmds);
		return (-1);
	}
	return (1);
}

int	ispipeexec(char **piped, t_mini *mini, char *line)
{
	int	i;

	i = 0;
	while (piped[i])
	{	
		if (fillcmd(piped[i], mini->envp, &mini->cmds[i]) != 0)
		{
			free (mini->cmds);
			return (-1);
		}
		i++;
	}
	free(piped);
	return (ispipe(line) + 1);
}

int	parse(t_mini *mini, char *line)
{
	char	**piped;

	if (checklineerr(line))
		return (-1);
	if (ispipe(line) == 0)
		return (nopipeexec(mini, line));
	else if (ispipe(line))
	{
		mini->cmds = malloc(sizeof (t_cmd) * (ispipe(line) + 2));
		if (!mini->cmds)
			exit (12);
		piped = ft_split(line, '|');
		return (ispipeexec(piped, mini, line));
	}
	return (-1);
}
