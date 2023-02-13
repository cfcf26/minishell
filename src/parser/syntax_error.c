#include "parse.h"

static int	pipe_syntax_error(t_list *node, t_list *next)
{
	t_token	*token;
	t_token	*next_token;

	if (next == NULL)
		return (SYNTAX_ERR);
	token = node->content;
	next_token = next->content;
	if (next_token->type == PIPE)
		return (SYNTAX_ERR);
	if (ft_strlen(token->ud.str) != 1)
		return (SYNTAX_ERR);
	return (0);
}

static int	redir_syntax_error(t_list *node, t_list *next)
{
	t_token	*token;
	t_token	*next_token;

	if (next == NULL)
		return (SYNTAX_ERR);
	token = node->content;
	next_token = next->content;
	if (next_token->type == REDIR)
		return (SYNTAX_ERR);
	if (ft_strlen(token->ud.str) > 2)
		return (SYNTAX_ERR);
	return (0);
}

int	check_syntax_error(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	if (((t_token *)tmp->content)->type == PIPE)
		return (SYNTAX_ERR);
	while (tmp)
	{
		if (tmp->content && ((t_token *)tmp->content)->type == PIPE)
		{
			if (pipe_syntax_error(tmp, tmp->next))
				return (SYNTAX_ERR);
		}
		else if (tmp->content && ((t_token *)tmp->content)->type == REDIR)
		{
			if (redir_syntax_error(tmp, tmp->next))
				return (SYNTAX_ERR);
		}
		tmp = tmp->next;
	}
	return (0);
}
