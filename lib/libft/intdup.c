/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:41:18 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:41:19 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*intdup(int src)
{
	int	*dup;

	dup = ft_malloc_guard(sizeof(int));
	*dup = src;
	return (dup);
}
