#ifndef FT_ERROR_H
# define FT_ERROR_H

#include "minishell.h"

typedef enum e_errno
{
	EINTR = 1,
	ESYNTAX = 258,
}	t_errno;

void	ft_perror(void);

#endif