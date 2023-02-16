#include "utils.h"
#include <stdio.h>

int	print_err_code(void)
{
	if (data()->err)
	{
		printf("Error code: %d", data()->err);
		return (1);
	}
	return (0);
}
