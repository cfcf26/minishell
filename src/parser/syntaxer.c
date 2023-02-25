#include "parse.h"

int	syntaxer(t_list **lst)
{
	if (check_syntax_error(*lst))
	{
		print_err(NULL, NULL, "syntax error", 258);
		return (258);
	}
	if (organize_token_list_by_type(lst))
		return (1);
	return (0);
}
