/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_return.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:38:11 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:38:12 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	free_all_return(t_list *tokens, int err_code, t_action_1 del)
{
	ft_lstclear(&tokens, del);
	return (err_code);
}
