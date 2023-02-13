#include "libft.h"

int	*intdup(int src)
{
	int	*dup;

	dup = ft_malloc_guard(sizeof(int));
	*dup = src;
	return (dup);
}
