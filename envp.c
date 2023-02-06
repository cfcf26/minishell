/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juykang <juykang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:13:34 by juykang           #+#    #+#             */
/*   Updated: 2023/02/06 14:07:06 by juykang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_envp_key(char *envp)
{
	int		i;
	int		len;
	char	*res;

	if (!envp)
		return (NULL);
	len = 1;
	while (envp[len] != '\0' && envp[len] != '=')
		len++;
	res = (char *)malloc(sizeof(char) * len + 1);
	i = 0;
	while (i < len)
	{
		res[i] = envp[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*get_envp_value(char *envp)
{
	char	*res;

	res = ft_strchr(envp, '=') + 1;
	return (res);
}

t_envp_list	*envp_new_node(void)
{
	t_envp_list	*tmp;

	tmp = (t_envp_list *)malloc(sizeof(t_envp_list));
	if (!tmp)
		return (NULL);
	tmp->key = NULL;
	tmp->value = NULL;
	tmp->len = 1;
	tmp->next = NULL;
	return (tmp);
}

t_envp_list	*set_envp_list(char **envp)
{
	t_envp_list	*list;
	t_envp_list	*head;

	list = envp_new_node();
	head = list;
	while (*envp)
	{
		list->key = get_envp_key(*envp);
		list->value = get_envp_value(*envp);
		list->len++;
		list->next = envp_new_node();
		list = list->next;
		envp++;
	}
	return (head);
}
