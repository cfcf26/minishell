/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:38:50 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:38:51 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "model.h"
#include "minishell.h"
#include "execute.h"
#include "error.h"
#include "utils.h"

static t_list	*exe_expand_all(char **args)
{
	t_list	*exps;
	int		idx;

	exps = NULL;
	idx = -1;
	while (args[++idx])
		ft_lstadd_back(&exps, expanding(args[idx]));
	return (exps);
}

static int	run_select(t_list *parsed, t_list *exps, int use_pipe, int *pid)
{
	t_list	*reds;

	reds = token_filter(parsed, REDIR);
	if (is_single_builtin(use_pipe, exps))
	{
		if (run_builtin(reds, exps))
			return (free_all_return(reds, FT_ERROR, NULL));
	}
	else
	{
		if (run_process(use_pipe, reds, exps, pid))
			return (free_all_return(reds, FT_ERROR, NULL));
	}
	ft_lstclear(&reds, NULL);
	return (FT_SUCCESS);
}

int	run(t_list *parsed, int *pid)
{
	const t_token	*use_pipe = token_first(parsed, PIPE);
	const t_token	*cmd = token_first(parsed, CMD);
	t_list			*exps;

	*pid = 0;
	exps = NULL;
	if (cmd != NULL)
		exps = exe_expand_all(((t_token *)(cmd))->ud.cmd_type->args);
	if (use_pipe && pipe(data()->pipe_fd) == -1)
	{
		ft_lstclear(&exps, free);
		return (print_err(NULL, NULL, NULL, errno));
	}
	if (run_select(parsed, exps, use_pipe != NULL, pid))
	{
		ft_lstclear(&exps, free);
		return (FT_ERROR);
	}
	if (use_pipe)
	{
		close(data()->pipe_fd[PIPE_WRITE]);
		data()->pipe_last_fd = data()->pipe_fd[PIPE_READ];
	}
	ft_lstclear(&exps, free);
	return (FT_SUCCESS);
}
