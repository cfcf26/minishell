#include "libft.h"

static int	is_space(char c)
{
	return (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ');
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	value;

	sign = 1;
	value = 0;
	while (is_space(*str))
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1;
	while (*str >= '0' && *str <= '9')
	{
		if (value > (value * 10) + (*str - '0'))
		{
			if (sign == -1)
				return (0);
			else
				return (-1);
		}
		value = (value * 10) + (*str - '0');
		str++;
	}
	return (sign * value);
}
