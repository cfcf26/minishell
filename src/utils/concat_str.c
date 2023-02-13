#include "libft.h"

char	*concat_str(const char *p1, const char *str, const char *p2)
{
	char	*s1;
	char	*s2;

	s1 = ft_strjoin(p1, str);
	if (s1 == NULL)
		exit(1);
	s2 = ft_strjoin(s1, p2);
	if (s1 == NULL)
		exit(1);
	free(s1);
	return (s2);
}
