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

static void exe(t_token *token)
{
	if (token->type == PIPE)
	{
		if (pipe(token->ud.pipe_type->fd))
			exit(1); // pipe error
		data()->pipe_fd[PIPE_READ] = token->ud.pipe_type->fd[PIPE_READ];
		data()->pipe_fd[PIPE_WRITE] = token->ud.pipe_type->fd[PIPE_WRITE];
	}
	if (token->type == CMD)
	{
		t_list	*lst;
		int		idx;

		idx = -1;
		lst = NULL;
		while (token->ud.cmd_type->args[++idx])
			ft_lstadd_back(&lst, expanding(token->ud.cmd_type->args[idx]));
		if (ft_lstsize(lst) == 0)
			exit(1); // 실행할 파일 없음
		token->ud.cmd_type->cmd = get_path(lst->content);
		int pid = fork();
		if (pid == 0)
			execve(token->ud.cmd_type->cmd, lst2arr(lst), lst2arr(data()->envp));
		if (pid == -1)
			exit(1); // fid error
		t_list *node = ft_lstnew(intdup(pid));
		if (node == NULL)
			exit(1); // null guard
		ft_lstadd_back(&(data()->waitpid_lst), node);
		ft_lstclear(&lst, free);
	}
	if (token->type == REDIR)
	{
		int 	type = token->ud.redir_type->redir_type;
		char 	*file = token->ud.redir_type->file;
		t_list 	*lst = expanding(file);
		int		fd;

		if (ft_lstsize(lst) != 1)
			exit(1); // ambiguous redirect
		if (type == IN)
			fd = open(lst->content, O_RDONLY);
		else if (type == OUT)
			fd = open(lst->content, O_WRONLY | O_TRUNC);
		else if (type == APPEND)
			fd = open(lst->content, O_WRONLY | O_APPEND);
		else
			exit(1); // unexpected case
		if (type == IN)
			dup2(fd, 0);
		else if (type == OUT || type == APPEND)
			dup2(fd, 1);
		close(fd);
		ft_lstclear(&lst, free);
	}
}

void execute(t_list *parsed_list)
{
	ft_lstiter(parsed_list, exe);
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
