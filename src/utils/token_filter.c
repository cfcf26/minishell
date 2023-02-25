/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_filter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:38:01 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:38:02 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*token_filter(t_list *lst, t_token_type type)
{
	t_list	*res;
	t_list	*node;

	res = NULL;
	while (lst)
	{
		if (((t_token *)(lst->content))->type == type)
		{
			node = ft_lstnew_guard(lst->content);
			ft_lstadd_back(&res, node);
		}
		lst = lst->next;
	}
	return (res);
}
