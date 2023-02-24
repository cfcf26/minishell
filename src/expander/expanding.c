#include "minishell.h"
#include "libstr.h"
#include "utils.h"
#include "expanding.h"

t_list	*expanding(char *str)
{
	t_list	*res;
	char	*fixed;

	fixed = expand_all(str);
	res = remove_quote(fixed);
	free(fixed);
	return (res);
}
