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

t_exp_data	expand_variables(char *str, t_exp_data *str_data, t_envp_list *list)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (str_data->quote == '\'' || str[i] != '$')
		{
			if (str[i] == '\"' || str[i] == '\'')
				str_data->quote = check_quote(str_data->quote, str[i]);
			str_data->len++;
			i++;
		}
		else if (str[i] == '$' && str_data->quote != '\'')
		{
			str_data->value = expand_env(str, i, str_data, list);
			str_data->str = strs_join(str, i, str_data);
			i = i + str_data->key_len;
			*str_data = reset_exp_data(str_data, 1);
		}
	}
	if (str_data->len > 1)
		str_data->str = strs_join(str, i, str_data);
	return (*str_data);
}

char	*expanding(char *str, t_envp_list *envp_list)
{
	char		*expanded_str;
	t_exp_data	str_data;
	t_envp_list	*envp_list;
	t_list		*res;

	res = ft_malloc_guard(sizeof(t_list *));
	envp_list = set_envp_list(envp);
	str_data = reset_exp_data(&str_data, 0);
	str_data = expand_variables(str, &str_data, envp_list);
	res->content = str_data->str;
	res->content = NULL;
	//split_exp_str(str_data->str, res);
	//remove_quote(res);
	return (res);
}
