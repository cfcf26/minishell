/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:38:08 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:38:09 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "utils.h"
#include "libstr.h"

char	*get_path(char *str)
{
	char	*path;
	char	**paths;
	char	*s;
	int		i;

	path = get_env("PATH");
	paths = ft_split(path, ':');
	free(path);
	if (paths == NULL)
		return (ft_strdup(str));
	i = -1;
	while (paths[++i])
	{
		s = str_concat(paths[i], "/", str);
		if (access(s, AT_EACCESS) == 0)
			break ;
		free(s);
		s = NULL;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (s);
}
