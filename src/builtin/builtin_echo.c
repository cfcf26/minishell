#include <stdio.h>
#include "builtin.h"

int	builtin_echo(t_list *argv)
{
	int	nextline;

	argv = argv->next;
	nextline = 1;
	if (argv)
	{
		if (ft_strncmp("-n", argv->content, 3) == 0)
			nextline = 0;
		else
			printf("%s", argv->content);
		argv = argv->next;
	}
	while (argv)
	{
		printf(" %s", argv->content);
		argv = argv->next;
	}
	if (nextline)
		printf("\n");
	return (0);
}
