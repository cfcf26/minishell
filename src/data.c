/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:37:50 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/27 10:58:49 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ms	*data(void)
{
	static t_ms	*ms;
	char		*pwd;

	if (ms != NULL)
		return (ms);
	ms = ft_malloc_guard(sizeof(t_ms));
	ft_memset(ms, 0, sizeof(t_ms));
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		exit(1);
	data()->pwd = pwd;
	return (ms);
}
