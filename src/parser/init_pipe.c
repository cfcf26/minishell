#include "parse.h"

t_list	*init_pipe(t_list **lst)
{
	t_list	*pipe_lst;

	((t_token *)(*lst)->content)->type = VISITED;
	pipe_lst = ft_lstnew_guard(ft_calloc_guard(1, sizeof(t_token)));
	((t_token *)pipe_lst->content)->type = PIPE;
	((t_token *)pipe_lst->content)->ud.pipe_type = \
	ft_calloc_guard(1, sizeof(t_pip));
	return (pipe_lst);
}
