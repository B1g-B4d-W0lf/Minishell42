/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 19:44:06 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/27 18:56:34 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execfillcmd(t_cmd *cmd, t_fill *fill, t_mini *mini)
{
	cmd->hd = malloc(countredir(fill->line) * sizeof(int));
	if (!cmd->hd)
		return (mallocerror(fill, mini));
	cmd->redir_type = sortredir(fill->line, cmd->hd);
	cmd->redir = countredir(fill->line);
	cmd->input_file = sortfiles(fill->line, '<');
	cmd->output_file = sortfiles(fill->line, '>');
	cmd->redir_in = countfiles(fill->line, '<');
	cmd->redir_out = countfiles(fill->line, '>');
	cmd->cmd = findcmd(fill->line);
	if (cmd->cmd)
		cmd->path = sendpath(&cmd->cmd[0], fill->paths);
}

int	fillcmd(char *str, t_mini *mini, t_cmd *cmd)
{
	t_fill	*fill;

	fill = malloc(1 * sizeof(t_fill));
	if (!fill)
		return (mallocerror(NULL, mini), -1);
	set_to_null_cmd(cmd);
	set_to_null_fill(fill);
	fill->paths = findpath(mini->envp);
	fill->spaced = expanding(str, mini->envp, cmd);
	fill->quote = malloc((countquotes(fill->spaced) + 1) * sizeof (char *));
	if (fill->quote == NULL)
		return (mallocerror(fill, mini), -1);
	fill->quote = sortquotes(fill->spaced, fill->quote);
	fill->spaced = spaceit(fill->spaced);
	fill->line = ft_split(fill->spaced, ' ');
	fill->line = addquoted(fill->line, fill->quote);
	if (!fill->line)
		return (freetfill(fill), -1);
	execfillcmd(cmd, fill, mini);
	freetfill(fill);
	return (0);
}

int	nopipeexec(t_mini *mini, char *line)
{
	mini->cmds = malloc(sizeof (t_cmd) * 2);
	if (!mini->cmds)
		exit (12);
	mini->nb_cmd = 1;
	if (fillcmd(ft_strdup(line), mini, &mini->cmds[0]) != 0)
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
	mini->nb_cmd = (ispipe(line) + 1);
	while (piped[i])
	{	
		if (fillcmd(piped[i], mini, &mini->cmds[i]) != 0)
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
