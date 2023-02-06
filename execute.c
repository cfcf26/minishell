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

// void	set_env(char *env)
// {
// 	if (1/* exist */)
// 		;// edit
// 	else if (1/* exist == false */)
// 		;// add
// }

char	*join_path(char *p1, char *p2)
{
	char	*s1;
	char	*s2;

	s1 = ft_strjoin(p1, "/");
	s2 = ft_strjoin(s1, p2);
	free(s1);
	return (s2);
}

static void	placeholder(t_list *argv)
{
	printf("------ %p ------\n", argv->content);
}

static void	*get_builtin_func(char *cmd)
{
	static const t_func	built[] = {
	{"echo", placeholder},
	{"cd", placeholder},
	{"pwd", placeholder},
	{"export", placeholder},
	{"unset", placeholder},
	{"env", placeholder},
	{"exit", placeholder},
	{NULL, NULL}
	};
	int					i;

	if (cmd == NULL)
		return (NULL);
	i = -1;
	while (built[++i].name)
		if (ft_strncmp(cmd, built[i].name, ft_strlen(built[i].name) + 1) == 0)
			return (built[i].func);
	return (NULL);
}

char	*get_path(char *str)
{
	char	*path;
	char	**paths;
	char	*s;
	int		i;

	path = get_env("PATH");
	paths = ft_split(path, ':');
	free(path);
	if (paths == NULL)
		return (ft_strdup(str));
	i = -1;
	while (paths[++i])
	{
		s = join_path(paths[i], str);
		if (access(s, AT_EACCESS) == 0)
			break ;
		free(s);
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	if (s == NULL || access(s, AT_EACCESS) != 0)
		return (ft_strdup(str));
	return (s);
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

// static void print_exe_test(t_list *lst)
// {
// 	t_token	*t;

// 	while (lst)
// 	{
// 		t = lst->content;
// 		if (t->type == PIPE)
// 			printf("PIPE\n");
// 		if (t->type == REDIR)
// 			printf("RED %d %s\n", t->ud.redir_type->redir_type, t->ud.redir_type->file);
// 		if (t->type == CMD)
// 			printf("CMD %s\n", t->ud.cmd_type->args[0]);
// 		lst = lst->next;
// 	}
// 	printf("\n");
// }

static t_list *token_filter(t_list *lst, t_token_type type)
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

static int redir(t_list *redir_lst)
{
	while (redir_lst)
	{
		t_red	*red = ((t_token *)(redir_lst->content))->ud.redir_type;
		t_list	*file = expanding(red->file);
		int		fd;

		if (ft_lstsize(file) != 1)
			exit(1); // ambiguous redirect
		fd = -1;
		if (red->redir_type == IN)
			fd = open(file->content, O_RDONLY);
		else if (red->redir_type == OUT)
			fd = open(file->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (red->redir_type == APPEND)
			fd = open(file->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
		ft_lstclear(&file, free);
		if (fd == -1)
		{
			ft_putstr_fd("this is error\n", STDERR_FILENO);
			return (1);
		}
		if (red->redir_type == IN && dup2(fd, STDIN_FILENO) == -1)
			exit(1); // dup2 error
		if (red->redir_type == OUT && dup2(fd, STDOUT_FILENO) == -1)
			exit(1); // dup2 error
		if (red->redir_type == APPEND && dup2(fd, STDOUT_FILENO) == -1)
			exit(1); // dup2 error
		close(fd);
		redir_lst = redir_lst->next;
	}
	return (0);
}

static t_list *exe_expand_all(char **args)
{
	t_list	*expandings;
	int		idx;

	expandings = NULL;
	idx = -1;
	while (args[++idx])
		ft_lstadd_back(&expandings, expanding(args[idx]));
	return (expandings);
}

static int	is_empty(t_list *lst)
{
	return (ft_lstsize(lst) == 0 || *((char *)(lst->content)) == 0);
}

static int	is_single_builtin(int use_pipe, char *cmd)
{
	return (!use_pipe && data()->waitpid_lst == NULL && get_builtin_func(cmd));
}

static void exe_body(int use_pipe, t_cmd *cmd, t_list *redir_lst, t_list *expandings)
{
	int	pid;

	if (use_pipe)
		pipe(data()->pipe_fd);
	pid = fork();
	if (pid == -1)
		exit(1); // pid error
	if (pid == 0)
	{
		if (data()->pipe_last_fd != -1)
		{
			dup2(data()->pipe_last_fd, STDIN_FILENO);
			close(data()->pipe_last_fd);
		}
		if (use_pipe)
		{
			close(data()->pipe_fd[PIPE_READ]);
			dup2(data()->pipe_fd[PIPE_WRITE], STDOUT_FILENO);
			close(data()->pipe_fd[PIPE_WRITE]);
		}
		if (redir(redir_lst) == 0)
			execve(cmd->cmd, lst2arr(expandings), lst2arr(data()->envp));
	}
	if (data()->pipe_last_fd != -1)
	{
		close(data()->pipe_last_fd);
		data()->pipe_last_fd = -1;
	}
	if (use_pipe)
		close(data()->pipe_fd[PIPE_WRITE]);
	if (use_pipe)
		data()->pipe_last_fd = data()->pipe_fd[PIPE_READ];
	t_list	*node = ft_lstnew(intdup(pid));
	if (node == NULL)
		exit(1); // null guard
	ft_lstadd_back(&(data()->waitpid_lst), node);
}

static void run_builtin(t_list *redir_lst, t_list *expandings)
{
	void (*func)(t_list *argv);

	if (redir(redir_lst) != 0)
		return ;
	
	func = get_builtin_func(expandings->content);
	func(expandings);
}

static void exe(t_list *lst)
{
	t_list	*cmd_lst;
	t_list	*redir_lst;
	t_list	*pipe_lst;
	t_list	*expandings;
	t_cmd	*cmd;

	cmd_lst = token_filter(lst, CMD);
	redir_lst = token_filter(lst, REDIR);
	pipe_lst = token_filter(lst, PIPE);
	cmd = ((t_token *)(cmd_lst->content))->ud.cmd_type;
	expandings = exe_expand_all(cmd->args);
	if (is_empty(expandings))
	{
		ft_lstclear(&expandings, free);
		return ;
	}
	if (is_single_builtin(pipe_lst != NULL, expandings->content))
		run_builtin(redir_lst, expandings);
	else
	{
		cmd->cmd = get_path(expandings->content);
		exe_body(pipe_lst != NULL, cmd, redir_lst, expandings);
		free(cmd->cmd);
	}
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

static void backup_stdio_fd()
{
	data()->backup_stdio_fd[STDIN_FILENO] = dup(STDIN_FILENO);
	data()->backup_stdio_fd[STDOUT_FILENO] = dup(STDOUT_FILENO);
}

static void reload_stdio_fd()
{
	dup2(data()->backup_stdio_fd[STDIN_FILENO], STDIN_FILENO);
	close(data()->backup_stdio_fd[STDIN_FILENO]);
	dup2(data()->backup_stdio_fd[STDOUT_FILENO], STDOUT_FILENO);
	close(data()->backup_stdio_fd[STDOUT_FILENO]);
}

static int	wait_pipe_processes(t_list *waitpids)
{
	int	err;
	int	pid;

	while (waitpids)
	{
		pid = *((int *)(waitpids->content));
		if (waitpids->next == NULL)
			waitpid(pid, &err, 0);
		else
			waitpid(pid, NULL, 0);
		waitpids = waitpids->next;
	}
	return (err);
}

void execute(t_list *parsed_list)
{
	t_list	*next;

	backup_stdio_fd();
	data()->pipe_last_fd = -1;
	while (next_cmd(&parsed_list, &next))
	{
		exe(next);
		ft_lstclear(&next, NULL);
	}
	data()->err = wait_pipe_processes(data()->waitpid_lst);
	ft_lstclear(&(data()->waitpid_lst), free);
	reload_stdio_fd();
}
