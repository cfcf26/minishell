/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iscontain.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 22:47:05 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/16 22:47:18 by yonshin          ###   ########.fr       */
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