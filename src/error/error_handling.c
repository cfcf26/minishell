#include "ft_error.h"

static char	*get_error_message(int errnum)
{
	if (errnum == ESYNTAX)
		return ("Operation not permitted");
	else if (errnum == EINTR)
		return ("Interrupted system call");
	else
		return ("Unknown error");
}

void	ft_perror(void)
{
	const char	*err_msg = get_error_message(data()->err);

	if (data()->err == EINTR)
		return ;
	write(2, "minishell: ", 11);
	write(2, err_msg, ft_strlen(err_msg));
	write(2, "\n", 1);
}
