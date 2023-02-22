#include "parse.h"

static t_redir_type	init_red_type(char *str)
{
	t_redir_type	redir_type;
	const int		len = ft_strlen(str);

	redir_type = 0;
	if (len == 1)
	{
		if (str[0] == '>')
			redir_type = OUT;
		else if (str[0] == '<')
			redir_type = IN;
	}
	else if (len == 2)
	{
		if (str[0] == '>' && str[1] == '>')
			redir_type = APPEND;
		else if (str[0] == '<' && str[1] == '<')
			redir_type = HEREDOC;
	}
	return (redir_type);
}

static void	red_token_lst_add_back(t_list **redir_lst, t_list *tmp)
{
	t_token	*redir_token;
	t_red	*redir;
	char	*file;

	((t_token *)tmp->content)->type = VISITED;
	((t_token *)tmp->next->content)->type = VISITED;
	redir_token = (t_token *)ft_calloc_guard(1, sizeof(t_token));
	redir_token->type = REDIR;
	redir = (t_red *)ft_calloc_guard(1, sizeof(t_red));
	redir->redir_type = init_red_type(((t_token *)tmp->content)->ud.str);
	if (redir->redir_type == HEREDOC)
	{
		file = heredoc(((t_token *)tmp->next->content)->ud.str);
		if (file == NULL)
			data()->parse_err = EINTR;
	}
	else
		file = ft_strdup_guard(((t_token *)tmp->next->content)->ud.str);
	redir->file = file;
	redir_token->ud.redir_type = redir;
	ft_lstadd_back(redir_lst, ft_lstnew_guard(redir_token));
}

static t_list	*create_redir_token_list(t_list *tmp)
{
	t_list	*redir_lst;

	redir_lst = NULL;
	while (tmp && ((t_token *)tmp->content)->type != PIPE)
	{
		if (((t_token *)tmp->content)->type == REDIR)
			red_token_lst_add_back(&redir_lst, tmp);
		if (data()->parse_err)
			return (NULL);
		tmp = tmp->next;
	}
	return (redir_lst);
}

t_list	*init_redir_lst(t_list **lst)
{
	t_list	*tmp;
	t_list	*redir_lst;

	tmp = *lst;
	redir_lst = create_redir_token_list(tmp);
	if (redir_lst == NULL)
		return (NULL);
	return (redir_lst);
}
