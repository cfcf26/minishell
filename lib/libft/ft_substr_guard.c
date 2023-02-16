#include "libft.h"

char	*ft_substr_guard(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	sub = ft_substr(s, start, len);
	if (!sub)
		exit(1);
	return (sub);
}
