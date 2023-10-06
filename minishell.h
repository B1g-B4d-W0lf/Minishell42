/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:31:41 by wfreulon          #+#    #+#             */
/*   Updated: 2023/09/28 21:54:12 by wfreulon         ###   ########.fr       */
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
	char	**token;
	int		nbr;
}		t_cmd;
typedef struct s_mini
{
	char 	**paths;
	char	*input;
	t_cmd	**cmds;
	int		exit;
}		t_mini;

//main.c

//parsing.c
t_mini	parse(t_mini *mini);
int		findchar(char *str, char c);

//parse_utils.c
int		symbolcount(char *str);
char	*spaceit(char *str);
void	addspace(int *i, int *j, char *spaced, char *str);
char	*findtoken(char *str);
int		ispipe(char *str);

//envp.c
char	**findpath(char **envp);

//free.c
void	cleanleak(t_mini *mini);
void	freedoubletab(char **tab);

//expand.c
char	**expanding(char **str);
int		sizeofdoubletab(char **tab);

//quotes.c
int insidequotes(char *str, int c);

#endif
