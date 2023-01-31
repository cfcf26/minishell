/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekwak <ekwak@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:43:51 by ekwak             #+#    #+#             */
/*   Updated: 2023/01/31 15:44:18 by ekwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ms	*data(void)
{
	static t_ms	*ms;

	if (ms != NULL)
		return (ms);
	ms = ft_malloc_guard(sizeof(t_ms));
	ft_memset(ms, 0, sizeof(t_ms));
	return (ms);
}
