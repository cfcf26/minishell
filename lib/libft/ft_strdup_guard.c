#include "libft.h"

char	*ft_strdup_guard(const char *s1)
{
	char	*dup;

	dup = ft_strdup(s1);
	if (!dup)
		exit(1);
	return (dup);
}
