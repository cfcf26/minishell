/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backup_stdio_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:39:08 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:39:10 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"

int	backup_stdio_fd(void)
{
	data()->backup_stdio_fd[STDIN_FILENO] = dup(STDIN_FILENO);
	if (data()->backup_stdio_fd[STDIN_FILENO] == -1)
		return (-1);
	data()->backup_stdio_fd[STDOUT_FILENO] = dup(STDOUT_FILENO);
	if (data()->backup_stdio_fd[STDOUT_FILENO] == -1)
		return (-1);
	return (0);
}
