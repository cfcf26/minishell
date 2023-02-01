/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juykang <juykang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:23:02 by juykang           #+#    #+#             */
/*   Updated: 2023/02/01 19:34:17 by juykang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_name(char c)
{
	const char	material[63] = "abcdefghijklmnopqrxtuvwxyz\
ABCDEFGHIJKLMNOPQRXTUVWXYZ0123456789_";

	if (ft_strnstr(&c, material, 63) != NULL)
		return (1);
	else
		return (0);
}

char	*find_key(char *str, int offset)
{
	int		i;
	char	*key;

	i = 1;
	if (str[offset + i] >= '0' && str[offset + i] <= '9')
		return (&(str[offset + i]));
	while (!is_valid_name(str[offset + i]))
		i++;
	key = ft_substr(str, offset, i);
	return (key);
}

char	*ft_lstncmp(char *str, char *key)
{
	t_ms	*ms;
	char	*value;

	ms = data();
	while (ms->envp)
	{
		if (key == ms->envp->content)
		{
			value = ms->envp->content;
			return (value);
		}
		ms->envp = ms->envp->next;
	}
	return (NULL);
}

void	*strs_join(char *str, int offset, t_exp_data *str_data)
{
	char	*res;
	char	*tmp;

	tmp = ft_strsub(str, offset - str_data->len, str_data->len);
	res = ft_strjoin(tmp, str_data->value);
	str_data->str = res;
	free(res);
}
