/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juykang <juykang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 22:35:16 by juykang           #+#    #+#             */
/*   Updated: 2023/02/01 22:30:52 by juykang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exp_data	*expand_variables(char *str)
{
	int			i;
	t_exp_data	*str_data;

	i = 0;
	while (str[i])
	{
		if (str[i] != '$')
		{
			str_data->len++;
			i++;
		}
		else
		{
			str_data->key = find_key(str, i);
			str_data->value = ft_lstncmp(str, str_data->key);
			strs_join(str, i, str_data);
			str_data->len = 0;
			i + str_data->key;
		}
	}
	if (str_data->len > 0)
		strs_join(str, i, str_data);
	return (str_data);
}

t_list	*expanding(char *str)
{
	char		*expanded_str;
	t_exp_node	*str_data;
	t_list		*res;

	res = ft_malloc(sizeof(t_list *));
	str_data = expand_variables(*str);
	split_exp_str(str_data->str, res);
	remove_quote(res);
	return (res);
}
