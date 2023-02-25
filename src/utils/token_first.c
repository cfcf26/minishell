/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_first.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:38:00 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:38:01 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_first(t_list *lst, t_token_type type)
{
	while (lst)
	{
		if (((t_token *)(lst->content))->type == type)
			return (lst->content);
		lst = lst->next;
	}
	return (NULL);
}
