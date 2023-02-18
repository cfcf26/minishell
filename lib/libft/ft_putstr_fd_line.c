#include "libft.h"

void	ft_putstr_fd_line(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}
