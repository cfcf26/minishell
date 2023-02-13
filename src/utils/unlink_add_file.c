#include "model.h"

void	unlink_add_file(char *path)
{
	ft_lstadd_front(&(data()->unlink_lst), ft_lstnew_guard(path));
}
