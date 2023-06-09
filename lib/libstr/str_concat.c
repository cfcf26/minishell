/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_concat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:39:35 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:39:36 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*str_concat(const char *p1, const char *str, const char *p2)
{
	char	*s1;
	char	*s2;

	s1 = ft_strjoin(p1, str);
	if (s1 == NULL)
		exit(1);
	s2 = ft_strjoin(s1, p2);
	if (s1 == NULL)
		exit(1);
	free(s1);
	return (s2);
}
