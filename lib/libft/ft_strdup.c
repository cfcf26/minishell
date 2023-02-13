/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:33:58 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/10 22:38:57 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*dup;

	size = 0;
	while (s1[size])
		size++;
	dup = ft_malloc_guard(sizeof(char) * size + 1);
	size = -1;
	while (s1[++size])
		dup[size] = s1[size];
	dup[size] = 0;
	return (dup);
}
