#include "minishell.h"

t_ms	*data(void)
{
	static t_ms	*ms;

	if (ms != NULL)
		return (ms);
	ms = ft_malloc_guard(sizeof(t_ms));
	ft_memset(ms, 0, sizeof(t_ms));
	return (ms);
}
