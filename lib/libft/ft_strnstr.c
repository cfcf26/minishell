#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		idx;

	if (*needle == 0)
		return ((char *)haystack);
	while (*haystack && len > 0)
	{
		idx = 0;
		while (haystack[idx] == needle[idx] && len - idx > 0)
		{
			idx++;
			if (needle[idx] == 0)
				return ((char *)haystack);
		}
		len--;
		haystack++;
	}
	return (0);
}
