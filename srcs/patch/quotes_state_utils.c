/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_state_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:40:02 by wfreulon          #+#    #+#             */
/*   Updated: 2023/11/29 17:40:03 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state	ft_process_base(char c, t_state state)
{
	if (c == '\'')
		return (s_quote);
	else if (c == '\"')
		return (d_quote);
	else
		return (state);
}

t_state	ft_process_single_quote(char c, t_state state)
{
	if (c == '\'')
		return (base);
	else if (c == '\"')
		return (double_in_single);
	else
		return (state);
}

t_state	ft_process_double_quote(char c, t_state state)
{
	if (c == '\"')
		return (base);
	else if (c == '\'')
		return (single_in_double);
	else
		return (state);
}

t_state	ft_process_single_in_double(char c, t_state state)
{
	if (c == '\'')
		return (d_quote);
	else if (c == '\"')
		return (base);
	else
		return (state);
}

t_state	ft_process_double_in_single(char c, t_state state)
{
	if (c == '\"')
		return (s_quote);
	else if (c == '\'')
		return (base);
	else
		return (state);
}
