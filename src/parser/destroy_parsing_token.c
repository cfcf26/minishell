/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_parsing_token.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:38:36 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:38:37 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"

void	destroy_parsing_token(void *content)
{
	t_token	*token;

	token = content;
	free(token->ud.str);
	free(token);
}
