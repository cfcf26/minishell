#include "model.h"

int	add_token(t_list **lst, t_token *token, int *err)
{
	if (token == NULL)
	{
		*err = 1;
		return (0);
	}
	ft_lstadd_back(lst, ft_lstnew(token));
	return (1);
}

t_token	*create_token(char *str)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = WORD;
	token->ud.str = str;
	return (token);
}
