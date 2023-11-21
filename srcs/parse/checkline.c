/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 20:21:20 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/21 15:55:07 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	havealphaornot(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) || str[i] == '$')
			count++;
		i++;
	}
	return (count);
}

char	symbolerrors(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|' && str[i + 1] == '|')
			return (str[i]);
		if ((str[i] == '>' && str[i + 1] == '<')
			|| (str[i] == '<' && str[i + 1] == '>'))
			return (str[i]);
		if (str[i] == '<' && str[i + 1] == '<'
			&& (str[i + 2] == '>' || str[i + 2] == '<'))
			return (str[i]);
		if (str[i] == '>' && str[i + 1] == '>'
			&& (str[i + 2] == '>' || str[i + 2] == '<'))
			return (str[i]);
		i++;
	}
	while (i > 1 && (str[i - 1] == ' ' || str[i - 1] == '	'))
		i--;
	if (str[i - 1] == '<' || str[i - 1] == '>' || str[i - 1] == '|')
		return (1);
	return (0);
}

int	checklineerr(char *str)
{
	if (symbolerrors(str) != 0)
	{
		if (symbolerrors(str) == 1)
			ft_printf("minishell: unexpected token at end of line\n");
		else if (symbolerrors(str) == '|')
			ft_printf("minishell: syntax error near unexpected token '|'\n");
		else if (symbolerrors(str) == '<')
			ft_printf("minishell: syntax error near unexpected token '<'\n");
		else if (symbolerrors(str) == '>')
			ft_printf("minishell: syntax error near unexpected token '>'\n");
		return (1);
	}
	return (0);
}
