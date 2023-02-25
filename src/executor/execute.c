/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:39:06 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:39:07 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execute.h"
#include "utils.h"
#include "builtin.h"
#include "libstr.h"
#include "libft.h"
#include "error.h"

static int	wait_pipe_processes(t_list *waitpids)
{
	int	err;
	int	pid;

	if (waitpids == NULL)
		return (FT_SUCCESS);
	init_signal_parent();
	err = 0;
	while (waitpids)
	{
		pid = *((int *)(waitpids->content));
		waitpid(pid, &err, 0);
		waitpids = waitpids->next;
	}
	init_signal();
	if (WIFSIGNALED(err))
		return (set_err(WTERMSIG(err) + 128));
	return (set_err(WEXITSTATUS(err)));
}

static int	next_cmd(t_list **lst, t_list **next)
{
	t_list	*node;

	*next = NULL;
	while (*lst && ((t_token *)((*lst)->content))->type != PIPE)
	{
		node = ft_lstnew_guard((*lst)->content);
		ft_lstadd_back(next, node);
		*lst = (*lst)->next;
	}
	if (*lst)
	{
		node = ft_lstnew_guard((*lst)->content);
		ft_lstadd_back(next, node);
		*lst = (*lst)->next;
	}
	return (*next != NULL);
}

int	execute(t_list *parsed_list)
{
	t_list	*next;
	t_list	*waitpid_node;
	int		waitpid;
	int		err;

	if (backup_stdio_fd())
		return (print_err(NULL, NULL, "backup io fail", 1));
	data()->pipe_last_fd = -1;
	err = FT_SUCCESS;
	while (err == 0 && next_cmd(&parsed_list, &next))
	{
		err = run(next, &waitpid);
		if (err == 0 && waitpid)
		{
			waitpid_node = ft_lstnew_guard(intdup(waitpid));
			ft_lstadd_back(&(data()->waitpid_lst), waitpid_node);
		}
		ft_lstclear(&next, NULL);
	}
	if (data()->waitpid_lst != NULL)
		err = wait_pipe_processes(data()->waitpid_lst);
	ft_lstclear(&(data()->waitpid_lst), free);
	if (reload_stdio_fd())
		return (print_err(NULL, NULL, "reload io fail", 1));
	return (err);
}
