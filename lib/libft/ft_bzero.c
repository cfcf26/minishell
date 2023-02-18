#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*cursor;
	size_t			idx;

	cursor = (unsigned char *)s;
	idx = 0;
	while (idx < n)
		cursor[idx++] = 0;
}
