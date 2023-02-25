/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:39:22 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:39:23 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "utils.h"
#include "builtin.h"
#include "error.h"

static char	*get_key(char *str)
{
	int	i;

	if (str == NULL || *str == '=' || ft_isdigit(*str))
		return (NULL);
	i = 0;
	while (str[i] && ft_strchr(ENV_CHARSET, str[i]))
		i++;
	if (str[i] != '=')
		return (ft_strdup(str));
	return (ft_substr_guard(str, 0, i));
}

static int	print_variables(void)
{
	t_list	*lst;

	lst = data()->envp;
	while (lst)
	{
		printf("declare -x %s\n", (char *)lst->content);
		lst = lst->next;
	}
	return (0);
}

int	builtin_export(t_list *argv)
{
	char	*key;
	char	*delimiter;
	int		err;

	err = 0;
	if (argv->next == NULL)
		return (print_variables());
	while (argv)
	{
		argv = argv->next;
		if (argv == NULL)
			continue ;
		key = get_key(argv->content);
		if (key == NULL)
		{
			err = 1;
			print_err("export", argv->content, "not a valid identifier", 1);
			continue ;
		}
		delimiter = ft_strchr(argv->content, '=');
		if (delimiter != NULL)
			set_env(key, delimiter + 1);
		free(key);
	}
	return (err);
}
