/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekwak <ekwak@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:40:23 by ekwak             #+#    #+#             */
/*   Updated: 2023/02/01 15:16:12 by ekwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_envp(char **envp)
{
	t_ms	*ms;
	int		i;
	// TODO

	// t_ms는 매개변수로 받지 않습니다. 이 값에 접근하기 위해 다음과 같이 접근할 수 있습니다.
	ms = data();
	i = 0;
	while (envp[i])
	{
		ft_lstadd_back(&ms->envp, ft_lstnew(ft_strdup(envp[i])));
		i++;
	}
}
