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

t_list	*init_new_node(void)
{
	t_list	*res;

	res = ft_malloc(t_list *);
	res->content = NULL;
	res->next = NULL;
	return (res);
}

int	split_str(char *str, int offset, t_list *node)
{
	char	quote;
	int		len;

	len = 0;
	while (str[offset + len] && (quote || ft_strchr(" \t\n\0|&;()", str[offset + len]) == 0))
	{
		if (quote == 0 && (str[offset + len] == '\'' || str[offset + len] == '\"'))
			quote = str[offset + len];
		else if (quote == '\'' && str[offset + len] == '\'')
			quote = 0;
		else if (quote == '\"' && str[offset + len] == '\"')
			quote = 0;
		len++;
	}
	if (len == 0)
		return (0);
	else
	{
		node->content = substr(str, len);
		return (len);
	}
}

t_list	*split_exp_str(char *str, t_list *head)
{
	t_list	*node;
	int		i;
	int		len;

	head = node;
	i = 0;
	len = 0;
	while (str[i])
	{
		node = init_new_node();
		len = split_str(str, i, node);
		node = node->next;
		i += len;
		len = 0;
	}
	return (head);
}
