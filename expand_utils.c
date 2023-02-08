/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juykang <juykang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:23:02 by juykang           #+#    #+#             */
/*   Updated: 2023/02/08 21:41:43 by juykang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_name(char c)
{
	const char	*material = "abcdefghijklmnopqrxtuvwxyz\
ABCDEFGHIJKLMNOPQRXTUVWXYZ0123456789_";

	if (ft_strchr(material, c) != NULL)
		return (1);
	else
		return (0);
}

char	*find_key(char *str, int offset, t_exp_data *str_data)
{
	int		i;
	char	*key;

	if (str[offset + 1] >= '0' && str[offset + 1] <= '9')
		return (&(str[offset + i]));
	i = 0;
	while (is_valid_name(str[offset + 1 + i]))
		i++;
	key = ft_substr(str, offset + 1, i);
	str_data->key_len = i + 1;
	return (key);
}

char	*expand_env(char *str, int offset, t_exp_data *str_data, \
t_envp_list *list)
{
	//t_ms	*ms;
	char		*value;
	t_envp_list	*tmp;

	//ms = data();
	str_data->key = find_key(str, offset, str_data);
	tmp = list;
	while (tmp->key)
	{
		if (ft_strnstr(str_data->key, tmp->key, ft_strlen(str_data->key)))
		{
			free(str_data->key);
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	free(str_data->key);
	return (NULL);
}

char	*strs_join(char *str, int offset, t_exp_data *str_data)
{
	char	*previous;
	char	*tmp;
	char	*res;

	previous = ft_substr(str, offset - str_data->len + 1, str_data->len - 1);
	if (str_data->value != NULL)
		res = ft_strjoin(previous, str_data->value);
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
			return (0);
		else if (last_quote == '\'')
			return ('\'');
		else
			return (now_quote);
	}
	else if (now_quote == '\'')
	{
		if (last_quote == '\"')
			return ('\"');
		else if (last_quote == '\'')
			return (0);
		else
			return (now_quote);
	}
	else
		return (now_quote);
}

char	*exception_dollor(char *str, t_exp_data *str_data)
{
	free(str_data->str);
	if (str[0] == '$' && str[1] == '\0')
		return ("$");
	else
		return ("86400");
}
