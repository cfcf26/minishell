#include "minishell.h"
//#include "lib/gnl/get_next_line.h"
#include "parse.h"

int ft_max(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}


char	*create_random_file(void)
{
	int			fd;
	const char	material[62] = "abcdefghijklmnopqrxtuvwxyz\
ABCDEFGHIJKLMNOPQRXTUVWXYZ0123456789";
	char		*file_name;
	char		*tmp_name;
	char		tmp[2];

	fd = open("/dev/urandom", O_RDONLY);
	file_name = ft_strdup("/tmp/pipex_tmp");
	tmp[1] = 0;
	while (!access(file_name, F_OK))
	{
		if (ft_strlen(file_name) > 128)
		{
			free(file_name);
			file_name = ft_strdup("/tmp/pipex_tmp");
		}
		read(fd, tmp, 1);
		tmp[0] = material[(unsigned char)tmp[0] % 62];
		tmp_name = ft_strjoin(file_name, tmp);
		free(file_name);
		file_name = tmp_name;
	}
	close(fd);
	return (file_name);
}

void	fill_tmp_file(int fd, char *limit)
{
	char	*buff;

	while (1)
	{
		write(1, "pipe heredoc> ", 15);
		buff = get_next_line(0);
		if (!buff)
			break ;
		if (ft_strncmp(buff, limit, ft_max(ft_strlen(buff) - 1, \
		ft_strlen(limit))) == 0)
			break ;
		write(fd, buff, ft_strlen(buff));
		free(buff);
	}
	free(buff);
}

void	here_doc_fork_signal(int fd, char *limit)
{
	int		pid;
	int		status;
	char	*buff;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		while (1)
		{
			write(1, "pipe heredoc> ", 15);
			buff = get_next_line(0);
			if (!buff)
				break ;
			if (ft_strncmp(buff, limit, ft_max(ft_strlen(buff) - 1, \
			ft_strlen(limit))) == 0)
				break ;
			write(fd, buff, ft_strlen(buff));
			free(buff);
		}
		free(buff);
		exit(0);
	}
	else
		waitpid(pid, &status, 0);
}

char	*heredoc(char *limit)
{
	char	*file_name;
	int		fd;

	file_name = create_random_file();
	fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		printf("infile error!");
	fill_tmp_file(fd, limit);
	close(fd);
	ft_lstadd_back(&data()->unlink_lst, ft_lstnew(file_name));
	return (file_name);
}

//void	print_syntax(t_list **lst)
//{
//	t_list	*tmp;
//	t_token	*token;

//	tmp = *lst;
//	while (tmp)
//	{
//		token = tmp->content;
//		if (token->type == CMD)
//			printf("CMD: %s\n", token->ud.cmd_type->cmd);
//		else if (token->type == PIPE)
//			printf("PIPE\n");
//		else if (token->type == REDIR)
//			printf("REDIR : %s\n", token->ud.redir_type->file);
//		tmp = tmp->next;
//	}
//}

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

t_redir_type	init_redir_type(char *str)
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
			((t_token *)tmp->content)->type = VISITED;
			((t_token *)tmp->next->content)->type = VISITED;
			if (redir_lst == NULL)
			{
				redir_lst = ft_lstnew(ft_calloc(1, sizeof(t_token)));
				redir_lst_tmp = redir_lst;
			}
			else
			{
				redir_lst_tmp = ft_lstnew(ft_calloc(1, sizeof(t_token)));
				ft_lstadd_back(&redir_lst, redir_lst_tmp);
			}
			((t_token *)redir_lst_tmp->content)->ud.redir_type = \
			ft_calloc(1, sizeof(t_red));
			((t_token *)redir_lst_tmp->content)->type = REDIR;
			((t_token *)redir_lst_tmp->content)->ud.redir_type->redir_type = \
			init_redir_type(((t_token *)tmp->content)->ud.str);
			if (((t_token *)redir_lst_tmp->content)->ud.redir_type->redir_type \
			== HEREDOC)
				((t_token *)redir_lst_tmp->content)->ud.redir_type->file = \
				heredoc(((t_token *)tmp->next->content)->ud.str);
			else
				((t_token *)redir_lst_tmp->content)->ud.redir_type->file = \
				ft_strdup(((t_token *)tmp->next->content)->ud.str);
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
	i = 0;
	while (tmp)
	{
		if (((t_token *)tmp->content)->type == PIPE)
			break ;
		if (((t_token *)tmp->content)->type == WORD)
		{
			((t_token *)tmp->content)->type = VISITED;
			args[i] = ft_strdup(((t_token *)tmp->content)->ud.str);
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
			cmd_lst = ft_lstnew(ft_calloc(1, sizeof(t_token)));
			((t_token *)cmd_lst->content)->ud.cmd_type = \
			ft_calloc(1, sizeof(t_cmd));
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
	pipe_lst = ft_lstnew(ft_calloc(1, sizeof(t_token)));
	((t_token *)pipe_lst->content)->type = PIPE;
	((t_token *)pipe_lst->content)->ud.pipe_type = ft_calloc(1, sizeof(t_pip));
	return (pipe_lst);
}

void	destory_tokenlst(t_list **lst)
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
