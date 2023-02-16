#include "utils.h"

t_token	*create_token(char *str)
{
	t_token	*token;

	token = (t_token *)ft_malloc_guard(sizeof(t_token));
	token->type = WORD;
	token->ud.str = str;
	return (token);
}
