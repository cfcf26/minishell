/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:38:03 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:38:04 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"

t_token	*to_token(t_list *node)
{
	if (node == NULL)
		return (NULL);
	return ((t_token *)(node->content));
}

t_red	*to_token_red(t_list *node)
{
	if (node == NULL)
		return (NULL);
	return (to_token(node)->ud.redir_type);
}

t_pip	*to_token_pip(t_list *node)
{
	if (node == NULL)
		return (NULL);
	return (to_token(node)->ud.pipe_type);
}

t_cmd	*to_token_cmd(t_list *node)
{
	if (node == NULL)
		return (NULL);
	return (to_token(node)->ud.cmd_type);
}
