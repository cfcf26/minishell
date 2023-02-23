#include "utils.h"

t_token	*create_token_word(char *str)
{
	t_token	*token;

	token = (t_token *)ft_calloc_guard(sizeof(t_token), 1);
	token->type = WORD;
	token->ud.str = str;
	return (token);
}
