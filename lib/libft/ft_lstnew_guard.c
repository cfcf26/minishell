#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew_guard(void *content)
{
	t_list	*node;

	node = ft_malloc_guard(sizeof(t_list));
	node->content = content;
	node->next = 0;
	return (node);
}
