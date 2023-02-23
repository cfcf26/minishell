#include "model.h"
#include "execute.h"

int	reload_stdio_fd(void)
{
	if (reopen(data()->backup_stdio_fd[STDIN_FILENO], STDIN_FILENO))
		return (-1);
	if (reopen(data()->backup_stdio_fd[STDOUT_FILENO], STDOUT_FILENO))
		return (-1);
	return (0);
}
