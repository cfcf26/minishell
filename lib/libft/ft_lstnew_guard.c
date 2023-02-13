/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_guard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 06:29:42 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/10 22:02:07 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew_guard(void *content)
{
	t_list	*node;

	node = ft_malloc_guard(sizeof(t_list));
	node->content = content;
	node->next = 0;
	return (node);
}
