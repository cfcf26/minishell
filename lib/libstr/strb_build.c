/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strb_build.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:39:41 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:39:42 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libstr.h"

char	*strb_build(t_strb *b)
{
	char		*res;
	int			idx;
	t_strb_item	*item;
	t_list		*lst;
	int			str_len;

	if (ft_lstsize(b->lst) == 0)
		return (NULL);
	res = ft_malloc_guard(sizeof(char) * (b->len + 1));
	res[b->len] = 0;
	idx = 0;
	lst = b->lst;
	while (lst)
	{
		item = lst->content;
		str_len = ft_strlen(item->str);
		ft_memcpy(res + idx, item->str, str_len);
		idx += str_len;
		lst = lst->next;
	}
	strb_clear(b);
	return (res);
}
