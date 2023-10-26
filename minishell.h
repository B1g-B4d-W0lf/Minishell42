/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:31:41 by wfreulon          #+#    #+#             */
/*   Updated: 2023/10/26 18:45:05 by wfreulon         ###   ########.fr       */
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
	char	**quote;
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
t_mini	parse(t_mini *mini, char **envp);
int		findchar(char *str, char c);

//parse_utils.c
int		symbolcount(char *str);
char	*spaceit(char *str);
void	addspace(int *i, int *j, char *spaced, char *str);
int		ispipe(char *str);

//envp.c : gestion des paths
char	**findpath(char **envp);
char	*sendpath(char *str, char **paths);
char	*ft_sup_join(char *s1, char c, char *s2);

//free.c : free les malloc
void	cleanleak(t_mini *mini);
void	freedoubletab(char **tab);

//expand.c : gestion expand
char	**expanding(char **str);
int		sizeofdoubletab(char **tab);

//quotes.c : gestion des quotes
int 	insidequotes(char *str, int pos);

//redir.c :gestion outfile et infile
char 	**sortfiles(char **str, char c);
int		countredir(char **str);
int		countfiles(char **str, char c);
int		*sortredir(char **str);

//splitjoin.c
char	*spaceitbis(char *str);
#endif
