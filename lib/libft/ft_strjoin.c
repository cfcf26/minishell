#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*result;
	char	*cursor;

	if (s1 == 0 || s2 == 0)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	result = (char *)malloc(sizeof(char) * len);
	if (result == 0)
		return (0);
	cursor = result;
	while (*s1)
		*cursor++ = *s1++;
	while (*s2)
		*cursor++ = *s2++;
	*cursor = 0;
	return (result);
}
