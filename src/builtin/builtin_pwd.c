#include <stdio.h>
#include "builtin.h"
#include "model.h"

int	builtin_pwd(t_list *argv)
{
	(void)argv;
	printf("%s\n", data()->pwd);
	return (0);
}
