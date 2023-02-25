#include "libft.h"
#include "model.h"
#include "minishell.h"
#include "execute.h"
#include "error.h"
#include "errno.h"
#include "libstr.h"
#include "builtin.h"

static void	close_pipe_last_fd(void)
{
	if (data()->pipe_last_fd != -1)
	{
		close(data()->pipe_last_fd);
		data()->pipe_last_fd = -1;
	}
}

static char	*get_accessible(t_list *exp)
{
	if (ft_strchr(exp->content, '/'))
		return (get_accessible_path(exp->content));
	return (get_accessible_file(exp->content));
}

static void	run_child(int use_pipe, t_list *red_lst, t_list *exp)
{
	char	*path;
	int		(*builtin_cmd)(t_list *argv);

	init_signal_child();
	if (data()->pipe_last_fd != -1)
		if (reopen(data()->pipe_last_fd, STDIN_FILENO))
			exit(errno);
	if (use_pipe)
	{
		close(data()->pipe_fd[PIPE_READ]);
		if (reopen(data()->pipe_fd[PIPE_WRITE], STDOUT_FILENO))
			exit(errno);
	}
	if (redir(red_lst))
		exit(errno);
	if (exp == NULL)
		exit(0);
	builtin_cmd = get_builtin_func(exp->content);
	if (builtin_cmd != NULL)
		exit(builtin_cmd(exp));
	path = get_accessible(exp);
	if (execve(path, lst2arr(exp), lst2arr(data()->envp)))
		exit(print_err(exp->content, NULL, NULL, errno));
}

int	run_process(int use_pipe, t_list *red_lst, t_list *exp, int *pid)
{
	*pid = fork();
	if (*pid == -1)
		return (print_err(exp->content, NULL, NULL, errno));
	if (*pid == 0)
		run_child(use_pipe, red_lst, exp);
	close_pipe_last_fd();
	return (FT_SUCCESS);
}
