/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:31:41 by wfreulon          #+#    #+#             */
/*   Updated: 2023/09/06 20:50:46 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef struct s_cmd
{
	char	**cmd;
	char	*path;
	char	token;
	int		nbr;
}		t_cmd;
typedef struct s_mini
{
	char 	**paths;
	char	**parsed;
	char	*input;
	t_cmd	*cmds;
	int		exit;
}		t_mini;

//main.c

//parsing.c
void	parse(t_mini *mini);
int		symbolcount(char *str);
char	*spaceit(char *str);

//envp.c
char	**findpath(char **envp);

#endif
