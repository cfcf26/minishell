#include "libft.h"

char	*get_next_line(int fd)
{
	static t_test	*list;
	int				err;

	if (fd < 0)
		return (0);
	err = 0;
	return (get_next_line_recursive(&list, fd, 0, &err));
}
