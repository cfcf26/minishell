#include "builtin.h"
#include "model.h"

int	builtin_cd(t_list *argv)
{
	argv = argv->next;
	if (chdir(argv->content))
	{
		ft_putstr_fd("error", 2);
		return (0);
	}
	free(data()->pwd);
	data()->pwd = getcwd(NULL, 0);
	return (0);
}
