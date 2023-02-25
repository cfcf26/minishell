/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:38:09 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:38:10 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"

char	*get_env(char *key)
{
	const int	size = ft_strlen(key);
	char		*var;
	t_list		*envps;

	if (ft_strncmp(key, "?", 2) == 0)
		return (ft_itoa(data()->err));
	envps = data()->envp;
	while (envps)
	{
		var = (char *)(envps->content);
		if (ft_strncmp(var, key, size) == 0 && var[size] == '=')
			return (ft_substr(var, size + 1, ft_strlen(var) - (size + 1)));
		envps = envps->next;
	}
	return (NULL);
}
