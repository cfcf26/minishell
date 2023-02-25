/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:38:28 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:38:29 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	arg_count(t_list *lst)
{
	t_list	*tmp;
	int		argc;

	argc = 0;
	tmp = lst;
	while (tmp && ((t_token *)tmp->content)->type != PIPE)
	{
		if (((t_token *)tmp->content)->type == WORD)
			argc++;
		tmp = tmp->next;
	}
	return (argc);
}

static char	**init_args(t_list *lst)
{
	const int	argc = arg_count(lst);
	t_list		*tmp;
	char		**args;
	int			i;

	if (argc == 0)
		return (NULL);
	args = ft_calloc_guard(argc + 1, sizeof(char *));
	args[argc] = NULL;
	tmp = lst;
	i = 0;
	while (tmp && ((t_token *)tmp->content)->type != PIPE)
	{
		if (((t_token *)tmp->content)->type == WORD)
		{
			((t_token *)tmp->content)->type = VISITED;
			args[i] = ft_strdup_guard(((t_token *)tmp->content)->ud.str);
			i++;
		}
		tmp = tmp->next;
	}
	return (args);
}

t_list	*init_cmd(t_list **lst)
{
	t_list	*tmp;
	t_list	*cmd_lst;

	tmp = *lst;
	cmd_lst = NULL;
	while (tmp && ((t_token *)tmp->content)->type != PIPE)
	{
		if (((t_token *)tmp->content)->type == WORD)
		{
			cmd_lst = ft_lstnew_guard(ft_calloc_guard(1, sizeof(t_token)));
			((t_token *)cmd_lst->content)->ud.cmd_type = \
			ft_calloc_guard(1, sizeof(t_cmd));
			((t_token *)cmd_lst->content)->type = CMD;
			((t_token *)cmd_lst->content)->ud.cmd_type->args = \
			init_args(tmp);
			break ;
		}
		tmp = tmp->next;
	}
	return (cmd_lst);
}
