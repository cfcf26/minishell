#include <stdio.h>
#include "libft.h"

void	*ft_malloc_guard(size_t size)
{
	void	*res;

	res = malloc(size);
	if (res == NULL)
	{
		perror("malloc fail");
		exit(1);
	}
	return (res);
}
