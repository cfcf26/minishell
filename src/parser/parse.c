#include "parse.h"

static void	tokenclear(void *token)
{
	if (((t_token *)token)->ud.str)
		free(((t_token *)token)->ud.str);
	free(token);
}

int	parse(char *line, t_list **result)
{	
	int	err;

	err = line_to_token(line, result);
	if (err != 0)
		ft_lstclear(result, tokenclear);
	err = syntaxer(result);
	if (err == SYNTAX_ERR)
		printf("syntax error\n");
	return (err);
}
