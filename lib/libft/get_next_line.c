/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:41:16 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:41:18 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static t_test	*list;
	int				err;

	if (fd < 0)
		return (0);
	err = 0;
	return (get_next_line_recursive(&list, fd, 0, &err));
}
