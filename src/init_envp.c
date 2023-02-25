/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:37:45 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:37:46 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_envp(char **envp)
{
	t_list	*node;

	while (envp[0])
	{
		node = ft_lstnew_guard(ft_strdup(*envp));
		ft_lstadd_back(&(data()->envp), node);
		envp++;
	}
}
