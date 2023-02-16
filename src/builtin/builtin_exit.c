#include "model.h"
#include "builtin.h"

int	builtin_exit(t_list *argv)
{
	exit(data()->err);
}
