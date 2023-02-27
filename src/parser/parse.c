/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:38:33 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:38:34 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "error.h"
#include "utils.h"

int	parse(char *line, t_list **result)
{
	data()->parse_err = 0;
	line_to_token(line, result);
	if (data()->parse_err)
	{
		ft_lstclear(result, (t_action_1)destroy_token);
		return (data()->parse_err);
	}
	else
	{
		data()->parse_err = syntaxer(result);
		if (data()->parse_err)
		{
			set_err(data()->parse_err);
			return (data()->parse_err);
		}
	}
	return (0);
}
