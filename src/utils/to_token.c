#include "model.h"

t_token	*to_token(t_list *node)
{
	return ((t_token *)(node->content));
}
