/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:41:03 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:41:04 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		idx;

	if (*needle == 0)
		return ((char *)haystack);
	while (*haystack && len > 0)
	{
		idx = 0;
		while (haystack[idx] == needle[idx] && len - idx > 0)
		{
			idx++;
			if (needle[idx] == 0)
				return ((char *)haystack);
		}
		len--;
		haystack++;
	}
	return (0);
}
