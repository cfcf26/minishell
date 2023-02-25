/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_guard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:40:43 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:40:44 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_guard(char const *s1, char const *s2)
{
	char	*join;

	join = ft_strjoin(s1, s2);
	if (!join)
		exit(1);
	return (join);
}
