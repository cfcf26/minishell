/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_accessible_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:39:02 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:39:02 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <unistd.h>
#include <error.h>
#include <stdlib.h>

char	*get_accessible_path(char *cmd)
{
	struct stat	st;

	stat(cmd, &st);
	if (access(cmd, F_OK) == -1)
		exit(print_err(cmd, NULL, "No such file or directory", 127));
	else if (S_ISDIR(st.st_mode))
		exit(print_err(cmd, NULL, "is a directory", 126));
	else if (access(cmd, X_OK) == -1)
		exit(print_err(cmd, NULL, "Permission denied", 126));
	else
		return (cmd);
}
