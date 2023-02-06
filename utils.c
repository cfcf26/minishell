#include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != 0)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == 0)
		return ((char *)s);
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*result;
	char	*cursor;

	if (s1 == 0 || s2 == 0)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	result = (char *)malloc(sizeof(char) * len);
	if (result == 0)
		return (0);
	cursor = result;
	while (*s1)
		*cursor++ = *s1++;
	while (*s2)
		*cursor++ = *s2++;
	*cursor = 0;
	return (result);
}

size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	while (s[size] != 0)
		size++;
	return (size);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		idx;

	if (*needle == 0)
		return ((char *)haystack);
	while (*haystack && len > 0)
	{
		idx = 0;
		while (haystack[idx] == needle[idx] && len - idx > 0)
		{
			idx++;
			if (needle[idx] == 0)
				return ((char *)haystack);
		}
		len--;
		haystack++;
	}
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	size;

	if (s == 0)
		return (0);
	size = ft_strlen(s);
	if (start > size)
		start = size;
	if (start + len > size)
		len = size - start;
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (result == 0)
		return (0);
	s = s + start;
	result[len] = 0;
	while (len-- > 0)
		result[len] = s[len];
	return (result);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (lst == 0 || new == 0)
		return ;
	if (*lst == 0)
		*lst = new;
	else
		ft_lstlast(*lst)->next = new;
}

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (node == 0)
		return (0);
	node->content = content;
	node->next = 0;
	return (node);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == 0)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}