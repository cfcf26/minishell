/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst2arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:38:06 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:38:07 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**lst2arr(t_list *lst)
{
	const int	size = ft_lstsize(lst);
	char		**arr;
	int			i;

	arr = ft_malloc_guard(sizeof(char *) * (size + 1));
	arr[size] = 0;
	i = -1;
	while (++i < size)
	{
		arr[i] = ft_strdup(lst->content);
		lst = lst->next;
	}
	return (arr);
}
