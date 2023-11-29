/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_fork_three.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:44:19 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/29 17:44:20 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned long long	ft_atoi_long_long(char *str)
{
	unsigned long long	i;
	unsigned long long	res;

	i = 0;
	res = 0;
	while (((str[i] >= 9 && str[i] <= 13) || str[i] == ' ') && str[i] != '\0')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res);
}
