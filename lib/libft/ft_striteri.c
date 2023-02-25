/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:40:42 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:40:43 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	idx;

	if (s == 0 || f == 0)
		return ;
	idx = 0;
	while (s[idx])
	{
		f(idx, s + idx);
		idx++;
	}
}
