#include "parse.h"

static void	destory_tokenlst(t_list **lst)
{
	t_list	*tmp;

	while ((*lst))
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free((((t_token *)tmp->content))->ud.str);
		free(tmp->content);
		free(tmp);
	}
}

int	organizetokenlst(t_list **lst)
{
	t_list	*tmp;
	t_list	*new_lst;

	tmp = *lst;
	new_lst = NULL;
	while (tmp)
	{
		ft_lstadd_back(&new_lst, init_redir_lst(&tmp));
		ft_lstadd_back(&new_lst, init_cmd(&tmp));
		if (tmp && ((t_token *)tmp->content)->type == PIPE)
			ft_lstadd_back(&new_lst, init_pipe(&tmp));
		tmp = tmp->next;
	}
	destory_tokenlst(lst);
	*lst = new_lst;
	return (0);
}

int	syntaxer(t_list **lst)
{
	if (check_syntax_error(*lst))
		return (SYNTAX_ERR);
	if (organizetokenlst(lst))
		return (SYNTAX_ERR);
	return (0);
}
