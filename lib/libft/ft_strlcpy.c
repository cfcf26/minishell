/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:40:56 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:40:57 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	n;

	n = 0;
	while (*src && n + 1 < dstsize)
	{
		dst[n] = *src;
		src++;
		n++;
	}
	if (dstsize > 0)
		dst[n] = 0;
	while (*src)
	{
		src++;
		n++;
	}
	return (n);
}
