/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:41:06 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:41:07 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	contains(char const *set, char c)
{
	if (set == 0)
		return (0);
	while (*set)
		if (*set++ == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	int		size;

	if (s1 == 0)
		return (0);
	if (set == 0)
		return (ft_strdup(s1));
	start = 0;
	size = 0;
	while (contains(set, s1[start]))
		start++;
	while (s1[start + size])
		size++;
	while (size != 0 && contains(set, s1[start + size - 1]))
		size--;
	return (ft_substr(s1, start, size));
}
