#include <unistd.h>

int	reopen(int fd1, int fd2)
{
	int	err;

	err = dup2(fd1, fd2);
	if (err == -1)
		return (err);
	close(fd1);
	return (0);
}
