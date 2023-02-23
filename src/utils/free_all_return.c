#include "libft.h"

int	free_all_return(t_list *tokens, int err_code, t_action_1 del)
{
	ft_lstclear(&tokens, del);
	return (err_code);
}
