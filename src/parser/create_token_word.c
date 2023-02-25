/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:38:25 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:38:26 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_token	*create_token_word(char *str)
{
	t_token	*token;

	token = (t_token *)ft_calloc_guard(sizeof(t_token), 1);
	token->type = WORD;
	token->ud.str = str;
	return (token);
}
