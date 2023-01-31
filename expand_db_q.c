/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_db_q.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juykang <juykang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:23:02 by juykang           #+#    #+#             */
/*   Updated: 2023/01/31 21:08:18 by juykang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_double_quote(char *str, int offset, int *len, t_exp_data *node)
{
	char		*res;
	int			i;

	i = 0;
	data()->envp;
	while (str[offset + i] != '\"')
	{
		if (str[i] == '$')
		{
			len = i + 1;
			res = expand_in_double_env();
		}
		i++;
	}
}
