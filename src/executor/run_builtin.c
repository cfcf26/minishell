#include "builtin.h"
#include "model.h"
#include "execute.h"

int	run_builtin(t_list *red_lst, t_list *cmd)
{
	int	(*func)(t_list *argv);

	if (redir(red_lst))
		return (FT_ERROR);
	func = get_builtin_func(cmd->content);
	return (func(cmd));
}
