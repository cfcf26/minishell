#include "model.h"

void	unlink_clear(void)
{
	ft_lstiter(data()->unlink_lst, (t_action_1)unlink);
	ft_lstclear(&(data()->unlink_lst), free);
}
