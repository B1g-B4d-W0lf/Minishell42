/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:31:41 by wfreulon          #+#    #+#             */
/*   Updated: 2023/07/29 19:47:29 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef struct s_mini
{
	char 	**paths;
	char	*input;
	int		exit;
}		t_mini;

//main.c

//parsing.c
int		symbolcount(char *str);
char	*spaceit(char *str);

//envp.c
char	**findpath(char **envp);

#endif
