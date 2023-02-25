/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:38:14 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:38:16 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_token	*create_token(t_token_type type)
{
	t_token	*token;

	token = ft_calloc_guard(1, sizeof(t_token));
	token->type = type;
	if (type == CMD)
		token->ud.cmd_type = ft_calloc_guard(1, sizeof(t_cmd));
	if (type == REDIR)
		token->ud.redir_type = ft_calloc_guard(1, sizeof(t_red));
	if (type == PIPE)
		token->ud.pipe_type = ft_calloc_guard(1, sizeof(t_pip));
	return (token);
}
