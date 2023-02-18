#include "libft.h"

int	ft_iscontain(char *all, char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_strchr(all, str[i]))
		i++;
	return (str[i] == '\0');
}