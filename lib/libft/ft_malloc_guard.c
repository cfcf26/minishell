/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_guard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:40:20 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:40:21 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

void	*ft_malloc_guard(size_t size)
{
	void	*res;

	res = malloc(size);
	if (res == NULL)
	{
		perror("malloc fail");
		exit(1);
	}
	return (res);
}
