/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:38:36 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:38:37 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	destroy_parsing_token(void *content)
{
	t_token	*token;

	token = content;
	free(token->ud.str);
	free(token);
}

int	syntaxer(t_list **lst)
{
	if (check_syntax_error(*lst))
	{
		print_err(NULL, NULL, "syntax error", 258);
		ft_lstclear(lst, (t_action_1)destroy_parsing_token);
		return (258);
	}
	if (organize_token_list_by_type(lst))
	{
		ft_lstclear(lst, (t_action_1)destroy_token);
		return (1);
	}
	return (0);
}
