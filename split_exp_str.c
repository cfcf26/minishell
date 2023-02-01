/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_exp_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juykang <juykang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 19:55:27 by juykang           #+#    #+#             */
/*   Updated: 2023/02/01 22:28:18 by juykang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	split_str(char *str, t_list *res)
{
	char	quote;
	int		len;

	len = 0;
	while (str[len] && (quote || ft_strchr(" \t\n|&;()<>", str[len]) == 0))
	{
		if (quote == 0 && (str[len] == '\'' || str[len] == '\"'))
			quote = str[len];
		else if (quote == '\'' && str[len] == '\'')
			quote = 0;
		else if (quote == '\"' && str[len] == '\"')
			quote = 0;
		len++;
	}
	res->content =
}

t_list	*split_exp_str(char *str)
{
	
}
