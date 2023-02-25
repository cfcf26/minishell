/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_accessible_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:39:03 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:39:04 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdlib.h>
#include "utils.h"
#include "libstr.h"
#include "error.h"

static int	find_file(char *directory, char *cmd, char **res)
{
	DIR				*dir;
	struct dirent	*file;

	*res = NULL;
	dir = opendir(directory);
	if (dir == NULL)
		return (FT_ERROR);
	file = readdir(dir);
	while (file != NULL)
	{
		if (file->d_type == DT_REG && \
			ft_strncmp(file->d_name, cmd, ft_strlen(cmd) + 1) == 0)
		{
			closedir(dir);
			*res = str_concat(directory, "/", cmd);
			return (FT_SUCCESS);
		}
		file = readdir(dir);
	}
	closedir(dir);
	return (FT_ERROR);
}

char	*get_accessible_file(char *cmd)
{
	char			*path;
	char			**paths;
	int				i;
	char			*file;

	path = get_env("PATH");
	if (path == NULL)
		exit(print_err(cmd, NULL, "command not found", 127));
	paths = ft_split(path, ':');
	i = -1;
	while (paths[++i])
		if (find_file(paths[i], cmd, &file) == FT_SUCCESS)
			break ;
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(path);
	if (file)
		return (file);
	exit(print_err(cmd, NULL, "command not found", 127));
}
