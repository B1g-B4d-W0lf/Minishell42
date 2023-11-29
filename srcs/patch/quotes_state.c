/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:40:17 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/29 17:40:18 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state	ft_get_state(char *s, int i)
{
	t_state	state;
	int		j;

	j = 0;
	state = base;
	while (j <= i)
	{
		if (state == base)
			state = ft_process_base(s[j], state);
		else if (state == s_quote)
			state = ft_process_single_quote(s[j], state);
		else if (state == d_quote)
			state = ft_process_double_quote(s[j], state);
		else if (state == single_in_double)
			state = ft_process_single_in_double(s[j], state);
		else if (state == double_in_single)
			state = ft_process_double_in_single(s[j], state);
		j++;
	}
	return (state);
}
