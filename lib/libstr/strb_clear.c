#include "libstr.h"

void	strb_clear(t_strb *b)
{
	t_list		*lst;
	t_strb_item	*item;
	
	b->len = 0;
	lst = b->lst;
	while (lst)
	{
		item = lst->content;
		if (item->del)
			item->del(item->str);
		lst = lst->next;
	}
	ft_lstclear(&b->lst, free);
}
