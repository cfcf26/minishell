/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:38:12 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:38:13 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"

static void	free_chars(char **arr)
{
	int	idx;

	if (arr == NULL)
		return ;
	idx = -1;
	while (arr[++idx])
		free(arr[idx]);
	free(arr);
}

void	destroy_token(t_token *token)
{
	if (token->type == CMD)
		free_chars(token->ud.cmd_type->args);
	if (token->type == REDIR)
		free(token->ud.redir_type->file);
	free(token->ud.str);
	free(token);
}
