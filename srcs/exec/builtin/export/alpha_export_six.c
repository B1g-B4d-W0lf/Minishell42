/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alpha_export_six.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:47:03 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/29 17:47:04 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_quotes(t_mini *minsh, char **temp_envp, char *str)
{
	char	*new;
	int		equ;

	equ = find_char(str, '=');
	if (equ == -1)
		new = ft_strdup(str);
	else
	{
		new = put_quotes_in_string(str, equ);
	}
	if (new == NULL)
	{
		free_t_mini(minsh);
		free_double_tab_char(temp_envp);
		exit(1);
	}
	return (new);
}

void	handle_error(t_mini *minsh, int position, char **temp_envp, char *str)
{
	char	*error;
	int		len;

	len = ft_split_len((minsh->cmds)[position].output_file) - 1;
	error = ft_strjoin_triple((minsh->cmds)[position].output_file[len] \
	, ": ", strerror(errno));
	print_error(error);
	free(str);
	free(error);
	free_double_tab_char(temp_envp);
	free_t_mini(minsh);
	exit(errno);
}

void	print_and_free(t_mini *minsh, int position, char **temp_envp)
{
	int		i;
	char	*str;

	i = 0;
	while (temp_envp[i])
	{
		str = add_quotes(minsh, temp_envp, (temp_envp[i]));
		if (printf("export : %s\n", str) == -1)
			handle_error(minsh, position, temp_envp, str);
		i++;
		free(str);
	}
	free_double_tab_char(temp_envp);
	return ;
}
