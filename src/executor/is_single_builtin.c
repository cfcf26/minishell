/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_single_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:39:00 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:39:01 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"
#include "builtin.h"

int	is_single_builtin(int use_pipe, t_list *cmd)
{
	const int	is_single = !use_pipe && data()->waitpid_lst == NULL;

	if (!is_single || cmd == NULL)
		return (0);
	return (get_builtin_func(cmd->content) != NULL);
}
