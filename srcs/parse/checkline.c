/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 20:21:20 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/12 21:00:56 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checklineerr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|' && str[i + 1] == '|')
			return(1);
		if ((str[i] == '>' && str[i + 1] == '<') || (str[i] == '<' && str[i + 1] == '>'))
			return(1);
		if (str[i] == '<' && str[i + 1] == '>' && (str[i + 2] == '>' || str[i + 2] == '<'))
			return (1);
		if (str[i] == '>' && str[i + 1] == '<' && (str[i + 2] == '>' || str[i + 2] == '<'))
			return (1);
		i++;
	}
	if (str[i - 1] == '<' || str[i - 1] == '>' || str[i - 1] == '|')
		return (1);
	return (0);
}
