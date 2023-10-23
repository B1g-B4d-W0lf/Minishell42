/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:31:41 by wfreulon          #+#    #+#             */
/*   Updated: 2023/10/21 23:12:34 by wfreulon         ###   ########.fr       */
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
	char	**infile;
	char	**outfile;
	int		redir;
	int		*redirtype;
	int		redin;
	int		redout;
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
int		ispipe(char *str);

//envp.c
char	**findpath(char **envp);
char	*sendpath(char *str, char **paths);

//free.c
void	cleanleak(t_mini *mini);
void	freedoubletab(char **tab);

//expand.c
char	**expanding(char **str);
int		sizeofdoubletab(char **tab);

//quotes.c
int 	insidequotes(char **str, int *pos);

//redir.c
char 	**sortfiles(char **str, char c);
int		countredir(char **str);
int		countfiles(char **str, char c);
int		*sortredir(char **str);

#endif
