/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc_guard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:39:51 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:39:52 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc_guard(size_t count, size_t size)
{
	size_t			total;
	unsigned char	*tmp;

	if (size && count > SIZE_MAX / size)
		return (0);
	total = count * size;
	tmp = ft_malloc_guard(total);
	if (tmp == 0)
		return (0);
	while (total-- > 0)
		tmp[total] = 0;
	return (tmp);
}
