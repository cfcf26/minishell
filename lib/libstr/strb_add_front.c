#include "libstr.h"

void	strb_add_front(t_strb *b, char *str, void (*del)(void *))
{
	t_strb_item	*item;

	if (str == NULL)
		return ;
	b->len += ft_strlen(str);
	item = ft_calloc_guard(1, sizeof(t_strb_item));
	item->str = str;
	item->del = del;
	ft_lstadd_front(&b->lst, ft_lstnew_guard(item));
}
