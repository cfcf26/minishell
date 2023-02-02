#include "minishell.h"

int	*intdup(int src)
{
	int	*dup;

	dup = ft_malloc_guard(sizeof(int));
	*dup = src;
	return (dup);
}

char	*get_env(char *str)
{
	const int	size = ft_strlen(str);
	char		*var;
	t_list		*envps;

	envps = data()->envp;
	while (envps)
	{
		var = (char *)(envps->content);
		if (ft_strncmp(var, str, size) == 0 && var[size] == '=')
			return (ft_substr(var, size + 1, ft_strlen(var) - (size + 1)));
		envps = envps->next;
	}
	return (NULL);
}

void	set_env(char *env)
{
	if (1/* exist */)
		;// edit
	else if (1/* exist == false */)
		;// add
}

char	*join_path(char *p1, char *p2)
{
	const int	size1 = ft_strlen(p1);
	const int	size2 = ft_strlen(p2);
	const char	*s1;
	const char	*s2;

	s1 = ft_strjoin(p1, "/");
	s2 = ft_strjoin(s1, p2);
	free(s1);
	return (s2);
}

char	*get_path(char *str)
{
	const char	*path = get_env("PATH");
	char		**paths = ft_split(path, ':');
	char		*s;
	int			i;

	paths = ft_split(path, ':');
	if (paths == NULL)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		s = join_path(paths[i], str);
		if (access(s, AT_EACCESS) == 0)
			return (s);
		free(s);
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
}

char	**lst2arr(t_list *lst)
{
	const int	size = ft_lstsize(lst);
	char		**arr;
	int			i;

	arr = malloc(sizeof(char *) * (size + 1));
	arr[size] = 0;
	i = -1;
	while (++i < size)
	{
		arr[i] = ft_strdup(lst->content);
		if (arr[i] == 0)
			exit(1);
		lst = lst->next;
	}
	return (arr);
}

// static void exe(t_token *token)
// {
// 	if (token->type == PIPE)
// 	{
// 		if (pipe(data()->pipe_fd))
// 			exit(1); // pipe error
// 	}
// 	if (token->type == CMD)
// 	{
// 		t_list	*lst;
// 		int		idx;

// 		idx = -1;
// 		lst = NULL;
// 		while (token->ud.cmd_type->args[++idx])
// 			ft_lstadd_back(&lst, expanding(token->ud.cmd_type->args[idx]));
// 		if (ft_lstsize(lst) == 0 || *((char *)(lst->content)) == 0)
// 			return; // 실행할 파일 없음
// 		token->ud.cmd_type->cmd = get_path(lst->content);
// 		int pid = fork();
// 		if (pid == 0)
// 			execve(token->ud.cmd_type->cmd, lst2arr(lst), lst2arr(data()->envp));
// 		if (pid == -1)
// 			exit(1); // pid error
// 		t_list *node = ft_lstnew(intdup(pid));
// 		if (node == NULL)
// 			exit(1); // null guard
// 		ft_lstadd_back(&(data()->waitpid_lst), node);
// 		ft_lstclear(&lst, free);
// 	}
// 	if (token->type == REDIR)
// 	{
// 		int 	type = token->ud.redir_type->redir_type;
// 		char 	*file = token->ud.redir_type->file;
// 		t_list 	*lst = expanding(file);
// 		int		fd;

// 		if (ft_lstsize(lst) != 1)
// 			exit(1); // ambiguous redirect
// 		if (type == IN)
// 			fd = open(lst->content, O_RDONLY);
// 		else if (type == OUT)
// 			fd = open(lst->content, O_WRONLY | O_TRUNC);
// 		else if (type == APPEND)
// 			fd = open(lst->content, O_WRONLY | O_APPEND);
// 		else
// 			exit(1); // unexpected case
// 		if (type == IN && dup2(fd, data()->pipe_fd[PIPE_READ]))
// 			exit(1); // dup2 error
// 		if (type == OUT && dup2(fd, data()->pipe_fd[PIPE_WRITE]))
// 			exit(1); // dup2 error
// 		if (type == APPEND && dup2(fd, data()->pipe_fd[PIPE_WRITE]))
// 			exit(1); // dup2 error
// 		close(fd);
// 		ft_lstclear(&lst, free);
// 	}
// }

static void print_exe_test(t_list *lst)
{
	t_token	*t;

	while (lst)
	{
		t = lst->content;
		if (t->type == PIPE)
			printf("PIPE\n");
		if (t->type == REDIR)
			printf("RED %d %s\n", t->ud.redir_type->redir_type, t->ud.redir_type->file);
		if (t->type == CMD)
			printf("CMD %s\n", t->ud.cmd_type->args[0]);
		lst = lst->next;
	}
	printf("\n");
}

static int	*next_token(t_list **lst, t_token **t)
{
	*t = NULL;
	if (*lst == NULL)
		return (NULL);
	*t = (*lst)->content;
	(*lst) = (*lst)->next;
	return (*t != NULL);
}

static t_list *token_filter(t_list *lst, int type)
{
	t_list	*res;
	t_list	*node;

	res = NULL;
	while (lst)
	{
		if (((t_token *)(lst->content))->type == type)
		{
			node = ft_lstnew(lst->content);
			if (node == NULL)
				exit(1); // malloc error
			ft_lstadd_back(&res, node);
		}
		lst = lst->next;
	}
	return (res);
}

static void redir(t_list *redir_lst)
{
	while (redir_lst)
	{
		t_red	*red = ((t_token *)(redir_lst->content))->ud.redir_type;
		t_list	*file = expanding(red->file);
		int		fd;

		if (ft_lstsize(file) != 1)
			exit(1); // ambiguous redirect
		if (red->redir_type == IN)
			fd = open(file->content, O_RDONLY);
		else if (red->redir_type == OUT)
			fd = open(file->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (red->redir_type == APPEND)
			fd = open(file->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			exit(1); // unexpected case
		if (fd != -1)
		{
			if (red->redir_type == IN && dup2(fd, STDIN_FILENO) == -1)
				exit(1); // dup2 error
			if (red->redir_type == OUT && dup2(fd, STDOUT_FILENO) == -1)
				exit(1); // dup2 error
			if (red->redir_type == APPEND && dup2(fd, STDOUT_FILENO) == -1)
				exit(1); // dup2 error
			close(fd);
		}
		ft_lstclear(&file, free);
		redir_lst = redir_lst->next;
	}
}

static void exe(t_list *lst)
{
	const t_list	*cmd_lst = token_filter(lst, CMD);
	const t_list	*redir_lst = token_filter(lst, REDIR);
	const t_list	*pipe_lst = token_filter(lst, PIPE);
	t_cmd			*cmd;
	t_list			*expandings;
	int				idx;

	cmd = ((t_token *)(cmd_lst->content))->ud.cmd_type;


	// expanding
	expandings = NULL;
	idx = -1;
	while (cmd->args[++idx])
		ft_lstadd_back(&expandings, expanding(cmd->args[idx]));


	// 실행할 프로그램의 절대경로를 가져옴
	if (ft_lstsize(expandings) == 0 || *((char *)(expandings->content)) == 0)
		return ; // 실행할 파일 없음
	cmd->cmd = get_path(expandings->content);


	// 실행
	pipe(data()->pipe_fd);
	int	pid = fork();
	if (pid == -1)
		exit(1); // pid error
	if (pid == 0)
	{
		redir(redir_lst);
		execve(cmd->cmd, lst2arr(expandings), lst2arr(data()->envp));
	}


	// 정리
	t_list	*node = ft_lstnew(intdup(pid));
	if (node == NULL)
		exit(1); // null guard
	ft_lstadd_back(&(data()->waitpid_lst), node);
	ft_lstclear(&expandings, free);
	ft_lstclear(&cmd_lst, NULL);
	ft_lstclear(&redir_lst, NULL);
}

int	next_cmd(t_list **lst, t_list **next)
{
	t_list	*node;

	*next = NULL;
	while (*lst && ((t_token *)((*lst)->content))->type != PIPE)
	{
		node = ft_lstnew((*lst)->content);
		if (node == NULL)
			exit(1); // malloc fail
		ft_lstadd_back(next, node);
		*lst = (*lst)->next;
	}
	if (*lst)
	{
		node = ft_lstnew((*lst)->content);
		if (node == NULL)
			exit(1); // malloc fail
		ft_lstadd_back(next, node);
		*lst = (*lst)->next;
	}
	return (*next != NULL);
}

void execute(t_list *parsed_list)
{
	t_list	*next;

	while (next_cmd(&parsed_list, &next))
	{
		exe(next);
		ft_lstclear(&next, NULL);
	}
	t_list *waitpids = data()->waitpid_lst;
	while (waitpids)
	{
		int pid = *((int *)(waitpids->content));
		if (waitpids->next == NULL)
			waitpid(pid, &(data()->err), 0);
		else
			waitpid(pid, NULL, 0);
		waitpids = waitpids->next;
	}
}
