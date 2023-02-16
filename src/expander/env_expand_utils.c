/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juykang <juykang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:23:26 by juykang           #+#    #+#             */
/*   Updated: 2023/02/17 00:10:40 by juykang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand.h"
#include "model.h"

int	is_valid_name(char c)
{
	const char	*material = "abcdefghijklmnopqrstuvwxyz\
ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_";

	if (c != 0 && ft_strchr(material, c) != NULL)
		return (1);
	else
		return (0);
}

char	*find_key(char *str, int offset, t_exp_data *str_data)
{
	int		i;
	char	*key;

	i = 0;
	while (is_valid_name(str[offset + 1 + i]))
		i++;
	key = ft_substr(str, offset + 1, i);
	str_data->key_len = i + 1;
	return (key);
}

// int	excpetion_check(char *str, int offset)
// {
// 	if (str[offset + 1] == '\0' || is_valid_name(str[offset + 1]) == 0)
// 		return (1);
// 	else
// 		return (0);
// }

char	*expand_env(char *str, int offset, t_exp_data *str_data)
{
	char	*value;

	// if (exception_check(str, offset))
	// {
	// 	exception_dollor(str, str_data);
	// 	return (value);
	// }
	str_data->key = find_key(str, offset, str_data);
	value = get_env(str_data->key);
	free(str_data->key);
	return (value);
}
