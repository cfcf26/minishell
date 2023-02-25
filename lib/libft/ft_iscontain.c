/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iscontain.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:39:58 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:39:59 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_iscontain(char *all, char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_strchr(all, str[i]))
		i++;
	return (str[i] == '\0');
}
