/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:38:40 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:38:41 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libstr.h"

static char	*cpy_without_quote(char *str, int len)
{
	int		size;
	int		i;
	char	*res;
	char	quote;

	res = ft_calloc_guard(1, ft_strlen(str) + 1);
	i = -1;
	size = 0;
	quote = 0;
	while (++i < len)
	{
		if (quote == str[i])
		{
			quote = 0;
			continue ;
		}
		if (quote == 0 && ft_strchr("'\"", str[i]))
		{
			quote = str[i];
			continue ;
		}
		res[size++] = str[i];
	}
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
