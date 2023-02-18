#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	size_t			size;
	unsigned int	idx;

	if (s == 0 || f == 0)
		return (0);
	size = 0;
	while (s[size])
		size++;
	result = (char *)malloc(sizeof(char) * (size + 1));
	if (result == 0)
		return (0);
	idx = -1;
	while (++idx < size)
		result[idx] = f(idx, s[idx]);
	result[size] = 0;
	return (result);
}
