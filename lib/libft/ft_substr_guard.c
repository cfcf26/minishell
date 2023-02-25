/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_guard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:41:08 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:41:09 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr_guard(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	sub = ft_substr(s, start, len);
	if (!sub)
		exit(1);
	return (sub);
}
