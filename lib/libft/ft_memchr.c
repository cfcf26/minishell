#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*cursor;
	size_t			idx;

	cursor = (unsigned char *)s;
	idx = -1;
	while (++idx < n)
	{
		if (cursor[idx] == (unsigned char)c)
			return (cursor + idx);
	}
	return (0);
}
