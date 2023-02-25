/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:40:26 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:40:27 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst_cursor;
	unsigned char	*src_cursor;
	size_t			idx;

	if (dst == 0 && src == 0)
		return (dst);
	dst_cursor = (unsigned char *)dst;
	src_cursor = (unsigned char *)src;
	if (dst < src)
	{
		idx = -1;
		while (++idx < len)
			dst_cursor[idx] = src_cursor[idx];
	}
	else
	{
		while (len-- > 0)
			dst_cursor[len] = src_cursor[len];
	}
	return (dst);
}
