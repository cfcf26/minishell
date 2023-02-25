/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:39:20 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:39:20 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "builtin.h"
#include "error.h"

int	builtin_unset(t_list *argv)
{
	char	*key;
	int		err;

	err = 0;
	argv = argv->next;
	while (argv)
	{
		key = argv->content;
		if (ft_iscontain(ENV_CHARSET, key) == 0)
		{
			err = 1;
			print_err("unset", key, "not a valid identifier", 1);
			argv = argv->next;
			continue ;
		}
		set_env(key, NULL);
		argv = argv->next;
	}
	return (err);
}
