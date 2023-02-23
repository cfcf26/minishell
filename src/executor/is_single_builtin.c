#include "model.h"
#include "builtin.h"

int	is_single_builtin(int use_pipe, t_list *cmd)
{
	const int	is_single = !use_pipe && data()->waitpid_lst == NULL;

	if (!is_single || cmd == NULL)
		return (0);
	return (get_builtin_func(cmd->content) != NULL);
}
