/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strb_add_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:39:37 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:39:39 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libstr.h"

void	strb_add_back(t_strb *b, char *str, void (*del)(void *))
{
	t_strb_item	*item;

	if (str == NULL)
		return ;
	b->len += ft_strlen(str);
	item = ft_calloc_guard(1, sizeof(t_strb_item));
	item->str = str;
	item->del = del;
	ft_lstadd_back(&b->lst, ft_lstnew_guard(item));
}
