/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 23:08:36 by alex              #+#    #+#             */
/*   Updated: 2023/11/29 17:42:58 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *str)
{
	int	original_stdout;
	int	original_stderr;

	original_stdout = dup(1);
	original_stderr = dup(2);
	dup2(2, 1);
	printf("%s", str);
	dup2(original_stdout, 1);
	dup2(original_stderr, 2);
	close(original_stderr);
	close(original_stdout);
	return ;
}
