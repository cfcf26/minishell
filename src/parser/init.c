#include "parse.h"

static t_redir_type	init_redir_type(char *str)
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

static t_list	*create_redir_token_list(t_list *tmp)
{
	t_list	*redir_lst;
	t_token	*redir_token;
	t_red	*redir;
	char	*file;

	redir_lst = NULL;
	while (tmp)
	{
		if (((t_token *)tmp->content)->type == PIPE)
			break ;
		if (((t_token *)tmp->content)->type == REDIR)
		{
			((t_token *)tmp->content)->type = VISITED;
			((t_token *)tmp->next->content)->type = VISITED;
			redir_token = (t_token *)ft_calloc_guard(1, sizeof(t_token));
			redir_token->type = REDIR;
			redir = (t_red *)ft_calloc_guard(1, sizeof(t_red));
			redir->redir_type = init_redir_type(((t_token *)tmp->content)->ud.str);
			if (redir->redir_type == HEREDOC)
				file = heredoc(((t_token *)tmp->next->content)->ud.str);
			else
				file = ft_strdup_guard(((t_token *)tmp->next->content)->ud.str);
			redir->file = file;
			redir_token->ud.redir_type = redir;
			ft_lstadd_back(&redir_lst, ft_lstnew_guard(redir_token));
		}
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
	return (redir_lst);
}


char	**init_args(t_list *lst)
{
	t_list	*tmp;
	char	**args;
	int		argc;
	int		i;

	argc = 0;
	tmp = lst;
	while (tmp)
	{
		if (((t_token *)tmp->content)->type == PIPE)
			break ;
		if (((t_token *)tmp->content)->type == WORD)
			argc++;
		tmp = tmp->next;
	}
	if (argc == 0)
		return (NULL);
	args = ft_calloc_guard(argc + 1, sizeof(char *));
	args[argc] = NULL;
	tmp = lst;
	i = 0;
	while (tmp)
	{
		if (((t_token *)tmp->content)->type == PIPE)
			break ;
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
	while (tmp)
	{
		if (((t_token *)tmp->content)->type == PIPE)
			break ;
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

t_list	*init_pipe(t_list **lst)
{
	t_list	*pipe_lst;

	((t_token *)(*lst)->content)->type = VISITED;
	pipe_lst = ft_lstnew_guard(ft_calloc_guard(1, sizeof(t_token)));
	((t_token *)pipe_lst->content)->type = PIPE;
	((t_token *)pipe_lst->content)->ud.pipe_type = ft_calloc_guard(1, sizeof(t_pip));
	return (pipe_lst);
}
