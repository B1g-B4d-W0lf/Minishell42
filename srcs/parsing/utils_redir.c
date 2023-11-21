/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:39:46 by jehubert          #+#    #+#             */
/*   Updated: 2023/06/29 18:47:36 by jehubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_tjoin(char *s1, char *s2)
{
	char	*res;
	size_t	totlen;

	if (!s2)
		return (NULL);
	totlen = ft_strlen(s1) + ft_strlen(s2);
	res = ft_calloc(sizeof(char), (totlen + 1));
	if (!res)
		return (NULL);
	ft_strlcat(res, (char *)s1, ft_strlen(s1) + 1);
	ft_strlcat(&res[ft_strlen(s1)], (char *)s2, ft_strlen(s2) + 1);
	return (free(s1), res);
}
