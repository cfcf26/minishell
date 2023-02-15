#include "utils.h"

char	*ft_strdup_guard(const char *s1)
{
	char	*dup;

	dup = ft_strdup(s1);
	if (!dup)
		exit(1);
	return (dup);
}

char	*ft_substr_guard(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	sub = ft_substr(s, start, len);
	if (!sub)
		exit(1);
	return (sub);
}

char	*ft_strjoin_guard(char const *s1, char const *s2)
{
	char	*join;

	join = ft_strjoin(s1, s2);
	if (!join)
		exit(1);
	return (join);
}
