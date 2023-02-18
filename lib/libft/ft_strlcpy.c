#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	n;

	n = 0;
	while (*src && n + 1 < dstsize)
	{
		dst[n] = *src;
		src++;
		n++;
	}
	if (dstsize > 0)
		dst[n] = 0;
	while (*src)
	{
		src++;
		n++;
	}
	return (n);
}
