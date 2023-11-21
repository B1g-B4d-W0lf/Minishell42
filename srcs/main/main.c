/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 04:52:33 by alex              #+#    #+#             */
/*   Updated: 2023/11/21 17:05:10 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

void	ft_end_loop(t_mini *mini, char *line)
{
	int			pid;
	extern int	g_status;

	free(line);
	line = NULL;
	pid = fork();
	signal(SIGINT, ctrlc);
	if (pid == 0)
	{
		signal(SIGINT, ctrl_c_here_doc);
		create_temp_files(mini);
		free_t_mini(mini);
		exit(0);
	}
	else
		wait(&pid);
	if (g_status != 130)
		create_file_for_dad(mini);
	if (fork_or_not(mini) == 1 && g_status != 130)
		no_fork(mini);
	else if (g_status != 130)
		exec(mini);
	send_act_cmd_for_unlink(mini);
	ft_free_cmds(mini->nb_cmd, mini);
}

void	set_signals(void)
{
	signal(SIGINT, handle_ctrlc);
	signal(SIGQUIT, SIG_IGN);
}

// void	printcmd(t_mini *mini, t_cmd *cmd)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (i < mini->nb_cmd)
// 	{
// 		while (cmd[i].cmd && cmd[i].cmd[j])
// 		{
// 			printf("cmd: %s\n", cmd[i].cmd[j]);
// 			j++;
// 		}
// 		j = 0;
// 		while (cmd[i].input_file[j])
// 		{
// 			printf("infile: %s\n", cmd[i].input_file[j]);
// 			j++;
// 		}
// 		j = 0;
// 		while (cmd[i].output_file[j])
// 		{
// 			printf("outfile: %s\n", cmd[i].output_file[j]);
// 			j++;
// 		}
// 		if (cmd[i].path)
// 			printf("path: %s\n", cmd[i].path);
// 		i++;
// 	}
// }

void	process_line(t_mini *mini, char *line)
{
	extern int	g_status;

	if (line != NULL)
	{
		if (ft_line_empty(line, 0))
			return ;
		add_history(line);
		mini->nb_cmd = parse(mini, line);
		printcmd(mini, mini->cmds);
		if (mini->nb_cmd == -1)
		{
			g_status = 2;
			free(line);
			return ;
		}
		g_status = 0;
		ft_end_loop(mini, line);
	}
}

void	clean_up(t_mini *mini)
{
	ft_clean_split(mini->envp);
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	t_mini		mini;
	char		*line;
	extern int	g_status;

	ft_start_main(argc, argv, envp, &mini);
	while (1)
	{
		set_signals();
		line = readline("minishell$> ");
		if (ft_line_empty(line, 1))
			break ;
		process_line(&mini, line);
	}
	clean_up(&mini);
	return (0);
}
