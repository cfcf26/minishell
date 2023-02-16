#include "libft.h"

char	*ft_strjoin_guard(char const *s1, char const *s2)
{
	char	*join;

	join = ft_strjoin(s1, s2);
	if (!join)
		exit(1);
	return (join);
}
