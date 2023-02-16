#include "parse.h"

static int	pipe_syntax_error(t_list *node, t_list *next)
{
	t_token	*token;
	t_token	*next_token;

	if (next == NULL)
		return (258);
	token = node->content;
	next_token = next->content;
	if (next_token->type == PIPE)
		return (258);
	if (ft_strlen(token->ud.str) != 1)
		return (258);
	return (0);
}

static int	redir_syntax_error(t_list *node, t_list *next)
{
	t_token	*token;
	t_token	*next_token;

	if (next == NULL)
		return (258);
	token = node->content;
	next_token = next->content;
	if (next_token->type == REDIR)
		return (258);
	if (ft_strlen(token->ud.str) > 2)
		return (258);
	return (0);
}

int	check_syntax_error(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	if (((t_token *)tmp->content)->type == PIPE)
	{
		data()->err = 258;
		return (258);
	}
	while (tmp)
	{
		if (tmp->content && ((t_token *)tmp->content)->type == PIPE)
		{
			if (pipe_syntax_error(tmp, tmp->next))
				return (258);
		}
		else if (tmp->content && ((t_token *)tmp->content)->type == REDIR)
		{
			if (redir_syntax_error(tmp, tmp->next))
				return (258);
		}
		tmp = tmp->next;
	}
	return (0);
}
