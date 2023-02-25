/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reload_stdio_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:38:58 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:38:59 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"
#include "execute.h"

int	reload_stdio_fd(void)
{
	if (reopen(data()->backup_stdio_fd[STDIN_FILENO], STDIN_FILENO))
		return (-1);
	if (reopen(data()->backup_stdio_fd[STDOUT_FILENO], STDOUT_FILENO))
		return (-1);
	return (0);
}
