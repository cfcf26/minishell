#include <unistd.h>
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;
	long	num;

	num = n;
	if (num < 0)
	{
		write(fd, "-", 1);
		num = -num;
	}
	c = (num % 10) + '0';
	if (num / 10 > 0)
		ft_putnbr_fd(num / 10, fd);
	write(fd, &c, 1);
}
