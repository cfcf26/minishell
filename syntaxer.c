/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekwak <ekwak@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:12:07 by ekwak             #+#    #+#             */
/*   Updated: 2023/02/02 11:02:12 by ekwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_syntax(t_list **lst)
{
	t_list	*tmp;
	t_token	*token;

	tmp = *lst;
	while (tmp)
	{
		token = tmp->content;
		if (token->type == CMD)
			printf("CMD: %s\n", token->ud.cmd_type->cmd);
		else if (token->type == PIPE)
			printf("PIPE\n");
		else if (token->type == REDIR)
			printf("REDIR : %s\n", token->ud.redir_type->file);
		tmp = tmp->next;
	}
}

int	pipe_syntax_error(t_list *node, t_list *next)
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

int	redir_syntax_error(t_list *node, t_list *next)
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
	while (lst)
	{
		if (lst->content && ((t_token *)lst->content)->type == PIPE)
		{
			if (pipe_syntax_error(lst, lst->next))
				return (SYNTAX_ERR);
		}
		else if (lst->content && ((t_token *)lst->content)->type == REDIR)
		{
			if (redir_syntax_error(lst, lst->next))
				return (SYNTAX_ERR);
		}
		lst = lst->next;
	}
	return (0);
}

int	syntaxer(t_list **lst)
{
	if (check_syntax_error(*lst))
		return (SYNTAX_ERR);
}

//void	syntaxer(t_list **lst, int *err)
//{
//	t_list	**tmp;
//	t_token	*token;

//	tmp = lst;
//	find_token(tmp, err, init_pipe, PIPE);
//	find_token(tmp, err, init_redir, REDIR);
//	find_token(tmp, err, init_cmd, WORD);
//	print_syntax(tmp);
//}
