/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:40:36 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:40:37 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	**next(char const *start, char c, int idx)
{
	int		size;
	char	**arr;

	while (*start && *start == c)
		start++;
	if (*start == 0)
		return ((char **)ft_calloc(idx + 1, sizeof(char *)));
	size = 0;
	while (start[size] && start[size] != c)
		size++;
	arr = next(start + size, c, idx + 1);
	if (arr == 0)
		return (0);
	arr[idx] = ft_substr(start, 0, size);
	if (arr[idx] == 0)
	{
		while (arr[++idx])
			free(arr[idx]);
		free(arr);
		return (0);
	}
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	if (s == 0)
		return (0);
	return (next(s, c, 0));
}
