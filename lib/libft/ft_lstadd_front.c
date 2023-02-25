/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:40:05 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:40:06 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*new_head;

	if (lst == 0 || new == 0)
		return ;
	new_head = new;
	while (new->next)
		new = new->next;
	new->next = *lst;
	*lst = new_head;
}
