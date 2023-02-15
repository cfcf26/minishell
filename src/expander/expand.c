/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekwak <ekwak@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 22:35:16 by juykang           #+#    #+#             */
/*   Updated: 2023/02/16 03:38:19 by ekwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand.h"
#include "model.h"

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
	if ((str[0] == '$' && str[1] == '\0') || (str[0] == '$' && str[1] == '?'))
		str_data->str = exception_dollor(str, str_data);
	return (*str_data);
}

t_list	*expanding(char *str)
{
	t_exp_data	str_data;
	t_envp_list	*envp_list;
	t_list		*res;

	char **envp = lst2arr(data()->envp);
	envp_list = set_envp_list(envp);
	str_data = reset_exp_data(&str_data, 0);
	str_data = expand_variables(str, &str_data, envp_list);
	res = split_exp_str(str_data.str, &str_data);
	remove_quote(res, &str_data);
	return (res);
}
