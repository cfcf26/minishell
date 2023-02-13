#include "minishell.h"
#include "execute.h"
#include "utils.h"

static int	placeholder(t_list *argv)
{
	printf("------ %p ------\n", argv->content);
	return (0);
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
		s = concat_str(paths[i], "/", str);
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

static void	*is_single_builtin(const t_token *use_pipe, t_list *expandings)
{
	const int		is_single = use_pipe == NULL && data()->waitpid_lst == NULL;

	if (!is_single || expandings == NULL)
		return (0);
	return (get_builtin_func(expandings->content));
}

static int run_process(const t_token *use_pipe, t_list *redir_lst, t_list *exp)
{
	const int	pid = fork();

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
		if (redir(redir_lst))
			exit(1);
		if (exp == NULL || exp->content == NULL)
			exit(0);
		if (execve(get_path(exp->content), lst2arr(exp), lst2arr(data()->envp)))
			exit(127);
	}
	if (data()->pipe_last_fd != -1)
	{
		close(data()->pipe_last_fd);
		data()->pipe_last_fd = -1;
	}
	return (pid);
}

static void run_builtin(t_list *redir_lst, t_list *expandings)
{
	void (*func)(t_list *argv);

	if (redir(redir_lst))
		return ;
	func = get_builtin_func(expandings->content);
	func(expandings);
}

static int exe(t_list *parsed)
{
	const t_token	*use_pipe = token_first(parsed, PIPE);
	const t_token	*cmd = token_first(parsed, CMD);
	t_list			*redirections;
	t_list			*expandings;
	int				pid;

	pid = 0;
	expandings = NULL;
	if (cmd != NULL)
		expandings = exe_expand_all(((t_token *)(cmd))->ud.cmd_type->args);


	if (use_pipe)
		pipe(data()->pipe_fd);


	redirections = token_filter(parsed, REDIR);
	if (is_single_builtin(use_pipe, expandings))
		run_builtin(redirections, expandings);
	else
		pid = run_process(use_pipe, redirections, expandings);


	if (use_pipe)
	{
		close(data()->pipe_fd[PIPE_WRITE]);
		data()->pipe_last_fd = data()->pipe_fd[PIPE_READ];
	}
	ft_lstclear(&redirections, NULL);
	return (pid);
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

static void	wait_pipe_processes(t_list *waitpids)
{
	int	err;
	int	pid;

	if (waitpids == NULL)
		return ;
	while (waitpids)
	{
		pid = *((int *)(waitpids->content));
		waitpid(pid, &err, 0);
		waitpids = waitpids->next;
	}
	data()->err = err;
}

void execute(t_list *parsed_list)
{
	t_list	*next;
	t_list	*waitpid_node;
	int		waitpid;

	backup_stdio_fd();
	data()->pipe_last_fd = -1;
	while (next_cmd(&parsed_list, &next))
	{
		waitpid = exe(next);
		if (waitpid)
		{
			waitpid_node = ft_lstnew_guard(intdup(waitpid));
			ft_lstadd_back(&(data()->waitpid_lst), waitpid_node);
		}
		ft_lstclear(&next, NULL);
	}
	wait_pipe_processes(data()->waitpid_lst);
	ft_lstclear(&(data()->waitpid_lst), free);
	reload_stdio_fd();
}
