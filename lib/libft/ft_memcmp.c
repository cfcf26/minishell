#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*cursor1;
	unsigned char	*cursor2;
	size_t			idx;

	cursor1 = (unsigned char *)s1;
	cursor2 = (unsigned char *)s2;
	idx = -1;
	while (++idx < n)
	{
		if (cursor1[idx] != cursor2[idx])
			return (cursor1[idx] - cursor2[idx]);
	}
	return (0);
}
