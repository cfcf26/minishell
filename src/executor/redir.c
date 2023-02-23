#include <fcntl.h>
#include "libft.h"
#include "model.h"
#include "utils.h"
#include "error.h"
#include "errno.h"
#include "minishell.h"

static int	open_file(t_red *red, int *fd)
{
	const t_list	*file = expanding(red->file);

	if (ft_lstsize((t_list *)file) != 1)
	{
		ft_lstclear((t_list **)(&file), free);
		return (print_err(red->file, NULL, "ambiguous redirection", 1));
	}
	*fd = -1;
	if (red->redir_type == IN || red->redir_type == HEREDOC)
		*fd = open(file->content, O_RDONLY);
	else if (red->redir_type == OUT)
		*fd = open(file->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (red->redir_type == APPEND)
		*fd = open(file->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd == -1)
	{
		print_err(file->content, NULL, NULL, FT_ERROR);
		ft_lstclear((t_list **)(&file), free);
		return (FT_ERROR);
	}
	ft_lstclear((t_list **)(&file), free);
	return (FT_SUCCESS);
}

static int	dup2fd(t_red *red, int fd)
{
	if (red->redir_type == IN && dup2(fd, STDIN_FILENO) == -1)
		return (print_err(red->file, NULL, NULL, errno));
	if (red->redir_type == HEREDOC && dup2(fd, STDIN_FILENO) == -1)
		return (print_err(red->file, NULL, NULL, errno));
	if (red->redir_type == OUT && dup2(fd, STDOUT_FILENO) == -1)
		return (print_err(red->file, NULL, NULL, errno));
	if (red->redir_type == APPEND && dup2(fd, STDOUT_FILENO) == -1)
		return (print_err(red->file, NULL, NULL, errno));
	close(fd);
	return (FT_SUCCESS);
}

int	redir(t_list *redir_lst)
{
	int	fd;

	while (redir_lst)
	{
		fd = -1;
		if (open_file(to_token_red(redir_lst), &fd))
			return (FT_ERROR);
		if (dup2fd(to_token_red(redir_lst), fd))
			return (FT_ERROR);
		redir_lst = redir_lst->next;
	}
	return (FT_SUCCESS);
}
