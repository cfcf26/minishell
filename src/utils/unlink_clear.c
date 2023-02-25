/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlink_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:37:58 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:37:59 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"

void	unlink_clear(void)
{
	ft_lstiter(data()->unlink_lst, (t_action_1)unlink);
	ft_lstclear(&(data()->unlink_lst), free);
}
