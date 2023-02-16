#include "parse.h"

int	organizetokenlst(t_list **lst)
{
	t_list	*tmp;
	t_list	*new_lst;

	tmp = *lst;
	new_lst = NULL;
	while (tmp)
	{
		ft_lstadd_back(&new_lst, init_redir_lst(&tmp));
		if (data()->parse_err)
			return (data()->parse_err);
		ft_lstadd_back(&new_lst, init_cmd(&tmp));
		if (tmp && ((t_token *)tmp->content)->type == PIPE)
			ft_lstadd_back(&new_lst, init_pipe(&tmp));
		tmp = tmp->next;
	}
	ft_lstclear(lst, tokenclear);
	*lst = new_lst;
	return (0);
}

int	syntaxer(t_list **lst)
{
	if (check_syntax_error(*lst))
		return (258);
	if (organizetokenlst(lst))
		return (1);
	return (0);
}
