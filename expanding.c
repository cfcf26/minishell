/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juykang <juykang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 22:35:16 by juykang           #+#    #+#             */
/*   Updated: 2023/02/01 15:08:45 by juykang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_array_size(char *str)
{
	while (*str)
	{
		if (*str == '$')
		{
			if(ft_strncmp(str, data()->envp, ))
		}
		else
			str++;
	}
}

void	check_expand_type(char *str)
{
	int			i;
	int			len;
	int			size;
	t_exp_data	**data;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			expand_double_quote(str, i, &len, data);
		else if (str[i] == '\'')
			expand_single_quote(str, i, &len, data);
		else if (str[i] == '$')
			expand_envp(str, i, &len, data);
		else
			expand_word(str, i, &len, data);
		i + len;
	}
}

t_list	*expanding(char *str)
{
	t_ms		*ms;
	t_exp_node	*res;

	ms = data();
	res = ft_malloc(sizeof(t_exp_node *));
	check_expand_type(str);
	res->str = remove_quote(str);
}
