/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:39:21 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:39:22 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "builtin.h"
#include "model.h"

int	builtin_pwd(t_list *argv)
{
	(void)argv;
	printf("%s\n", data()->pwd);
	return (0);
}
