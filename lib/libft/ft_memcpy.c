/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:40:24 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:40:25 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	unsigned char	*dst_cursor;
	unsigned char	*src_cursor;

	if (dst == 0 && src == 0)
		return (dst);
	dst_cursor = (unsigned char *)dst;
	src_cursor = (unsigned char *)src;
	while (len-- > 0)
		dst_cursor[len] = src_cursor[len];
	return (dst);
}
