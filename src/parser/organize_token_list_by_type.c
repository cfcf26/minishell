/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_token_list_by_type.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:38:32 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:38:33 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"

int	organize_token_list_by_type(t_list **lst)
{
	t_list	*tmp;
	t_list	*new_lst;

	tmp = *lst;
	new_lst = NULL;
	while (tmp)
	{
		ft_lstadd_back(&new_lst, init_redir_lst(&tmp));
		if (data()->parse_err)
		{
			ft_lstclear(lst, (t_action_1)destroy_parsing_token);
			ft_lstclear(&new_lst, (t_action_1)destroy_token);
			return (data()->parse_err);
		}
		ft_lstadd_back(&new_lst, init_cmd(&tmp));
		if (tmp && ((t_token *)tmp->content)->type == PIPE)
			ft_lstadd_back(&new_lst, init_pipe(&tmp));
		tmp = tmp->next;
	}
	ft_lstclear(lst, (t_action_1)destroy_parsing_token);
	*lst = new_lst;
	return (0);
}
