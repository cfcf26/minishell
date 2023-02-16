#include "parse.h"

int	parse(char *line, t_list **result)
{
	data()->parse_err = 0;
	line_to_token(line, result);
	if (data()->parse_err)
	{
		ft_lstclear(result, tokenclear);
		data()->err = data()->parse_err;
		return (data()->parse_err);
	}
	else
	{
		data()->parse_err = syntaxer(result);
		if (data()->parse_err)
		{
			ft_lstclear(result, tokenclear);
			data()->err = data()->parse_err;
			return (data()->parse_err);
		}
	}
	return (0);
}
