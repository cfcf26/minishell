/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekwak <ekwak@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:12:07 by ekwak             #+#    #+#             */
/*   Updated: 2023/02/02 17:02:36 by ekwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lib/libft/libft.h"

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
	if (((t_token *)lst->content)->type == PIPE)
		return (SYNTAX_ERR);
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

t_redir_type	init_redir_type(char *str)
{
	t_redir_type	redir_type;
	const int		len = ft_strlen(str);

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

t_list	*init_redir_lst(t_list **lst)
{
	t_list	*tmp;
	t_list	*redir_lst;
	t_list	*redir_lst_tmp;

	tmp = *lst;
	redir_lst = NULL;
	while (tmp)
	{
		if (((t_token *)tmp->content)->type == PIPE)
			break ;
		if (((t_token *)tmp->content)->type == REDIR)
		{
			if (redir_lst == NULL)
			{
				redir_lst = ft_lstnew(ft_calloc(1, sizeof(t_token)));
				redir_lst_tmp = redir_lst;
			}
			else
			{
				redir_lst_tmp = redir_lst;
				while (redir_lst_tmp->next)
					redir_lst_tmp = redir_lst_tmp->next;
				redir_lst_tmp->next = ft_lstnew(ft_calloc(1, sizeof(t_token)));
			}
			((t_token *)redir_lst_tmp->content)->ud.redir_type = \
			ft_calloc(1, sizeof(t_red));
			((t_token *)redir_lst_tmp->content)->type = REDIR;
			((t_token *)redir_lst_tmp->content)->ud.redir_type->file = \
			((t_token *)tmp->next->content)->ud.str;
			((t_token *)redir_lst_tmp->content)->ud.redir_type->redir_type = \
			init_redir_type(((t_token *)tmp->content)->ud.str);
			//if (((t_token *)redir_lst_tmp->content)->ud.redir_type->redir_type \
			//== HEREDOC)
			//	heredoc(&((t_token *)redir_lst_tmp->content)->ud.redir_type);
		}
		tmp = tmp->next;
	}
	return (redir_lst);
}

char	**init_args(t_list *lst)
{
	t_list	*tmp;
	char	**args;
	int		argc;
	int		i;

	i = 0;
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
	args = ft_calloc(argc + 1, sizeof(char *));
	args[argc] = NULL;
	tmp = lst;
	while (tmp)
	{
		if (((t_token *)tmp->content)->type == PIPE)
			break ;
		if (((t_token *)tmp->content)->type == WORD)
			args[i++] = ((t_token *)tmp->content)->ud.str;
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
			cmd_lst = ft_lstnew(ft_calloc(1, sizeof(t_token)));
			((t_token *)cmd_lst->content)->ud.cmd = \
			ft_calloc(1, sizeof(t_cmd));
			((t_token *)cmd_lst->content)->ud.cmd_type->cmd = \
			((t_token *)tmp->content)->ud.str;
			((t_token *)cmd_lst->content)->type = CMD;
			((t_token *)cmd_lst->content)->ud.cmd_type->args = \
			init_args(tmp->next);
			break ;
		}
		tmp = tmp->next;
	}
	return (cmd_lst);
}

t_list	*init_pipe(t_li)

int	organizetokenlst(t_list **lst)
{
	//기존의 token_list를 순회하며 파이프와 리다이렉션, 커맨드를 새로운 리스트로 만들어야함
	// 1. 파이프를 만나기 전까지 새 리스트에 리다이랙션을 넣는다.
	// 2. 파이프를 만나기 전까지 샐 리스트에 커맨드를 넣는다.
	// 3. 파이프를 만나면 새 리스트를 만들고 1,2번을 반복한다.
	t_list	*tmp;
	t_list	*new_lst;

	tmp = *lst;
	new_lst = NULL;
	while (tmp)
	{
		if (((t_token *)tmp->content)->type == REDIR)
			ft_lstadd_back(&new_lst, init_redir_lst(&tmp));
		else if (((t_token *)tmp->content)->type == WORD)
			ft_lstadd_back(&new_lst, init_cmd(&tmp));
		else if (((t_token *)tmp->content)->type == PIPE)
			ft_lstadd_back(&new_lst, init_pipe(&tmp));
	}
}

int	syntaxer(t_list **lst)
{
	if (check_syntax_error(*lst))
		return (SYNTAX_ERR);
	// 기존 리스트를 실행직전의 리스트로 바꿔야함
	// here_doc 처리 해야함

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
