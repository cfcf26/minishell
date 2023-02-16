/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juykang <juykang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:23:02 by juykang           #+#    #+#             */
/*   Updated: 2023/02/16 19:32:29 by juykang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand.h"
#include "model.h"

char	*strs_join(char *str, int offset, t_exp_data *str_data)
{
	char	*previous;
	char	*tmp;
	char	*res;

	previous = ft_substr(str, offset - str_data->len + 1, str_data->len - 1);
	if (str_data->value != NULL)
	{
		if (str_data->str == NULL)
			tmp = previous;
		else
			tmp = ft_strjoin(str_data->str, previous);
		res = ft_strjoin(tmp, str_data->value);
	}
	else
	{
		if (str_data->str == NULL)
			return (previous);
		res = ft_strjoin(str_data->str, previous);
	}
	free(previous);
	free(str_data->str);
	return (res);
}

t_exp_data	reset_exp_data(t_exp_data *node, int flag)
{
	if (flag == 0)
	{
		node->key = NULL;
		node->key_len = 1;
		node->len = 1;
		node->str = NULL;
		node->value = NULL;
		node->quote = '0';
	}
	else
	{
		node->key = NULL;
		node->key_len = 1;
		node->len = 1;
		node->value = NULL;
	}
	return (*node);
}

char	check_quote(char last_quote, char now_quote)
{
	if (now_quote == '\"')
	{
		if (last_quote == '\"')
			return ('0');
		else if (last_quote == '\'')
			return ('\'');
		else
			return ('\"');
	}
	else if (now_quote == '\'')
	{
		if (last_quote == '\"')
			return ('\"');
		else if (last_quote == '\'')
			return ('0');
		else
			return ('\'');
	}
	else
		return (now_quote);
}

char	*exception_dollor(char *str, t_exp_data *str_data)
{
	free(str_data->str);
	if (str[0] == '$' && str[1] == '\0')
		return ("$");
	// else
	//return (ft_itoa(error));
	return (0);
}
