#include "libft.h"
#include "libstr.h"

static char	*cpy_without_quote(char *str, int len)
{
	int		size;
	int		i;
	char	*res;

	i = -1;
	size = 0;
	while (++i < len)
		if (ft_strchr("'\"", str[i]) == 0)
			size++;
	res = ft_malloc_guard(size + 1);
	res[size] = 0;
	i = -1;
	size = 0;
	while (++i < len)
		if (ft_strchr("'\"", str[i]) == 0)
			res[size++] = str[i];
	return (res);
}

static char	*next(char **str)
{
	char	quote;
	int		len;
	char	*res;

	while (**str == ' ')
		(*str)++;
	if (**str == 0)
		return (NULL);
	len = -1;
	while ((*str)[++len] && (quote != 0 || (*str)[len] != ' '))
	{
		if ((*str)[len] == quote)
			quote = 0;
		else if ((*str)[len] == '\'' || (*str)[len] == '"')
			quote = (*str)[len];
	}
	res = cpy_without_quote(*str, len);
	(*str) += len;
	return (res);
}

t_list	*remove_quote(char *str)
{
	t_list	*res;
	char	*tmp;

	res = NULL;
	while (*str)
	{
		tmp = next(&str);
		if (tmp)
			ft_lstadd_back(&res, ft_lstnew_guard(tmp));
	}
	return (res);
}
