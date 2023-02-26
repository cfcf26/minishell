/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:38:45 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:38:49 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libstr.h"
#include "utils.h"

static char	*exception_case(char **str)
{
	if (**str == 0 || **str == ' ')
		return (ft_strdup("$"));
	if (**str && ft_isdigit(**str))
	{
		(*str)++;
		return (ft_strdup(""));
	}
	if (**str == '?')
	{
		(*str)++;
		return (ft_itoa(data()->err));
	}
	if (**str == '$')
	{
		(*str)++;
		return (ft_strdup("<processID>"));
	}
	return (NULL);
}

static char	*try_expand_value(char **str)
{
	int		len;
	char	*key;
	char	*value;

	if (**str != '$')
		return (NULL);
	(*str)++;
	value = exception_case(str);
	if (value)
		return (value);
	len = 0;
	while ((*str)[len] && ft_strchr(ENV_CHARSET, (*str)[len]))
		len++;
	key = ft_substr(*str, 0, len);
	(*str) += len;
	value = get_env(key);
	free(key);
	if (value == NULL)
		return (ft_strdup(""));
	return (value);
}

char	*expand_all(char *str)
{
	t_strb	strb;
	char	quote;
	int		len;

	strb_init(&strb);
	quote = 0;
	while (*str)
	{
		len = 0;
		while (str[len] && (quote != 0 || str[len] != '$'))
		{
			if (str[len] == quote)
				quote = 0;
			else if (str[len] == '\'')
				quote = str[len];
			len++;
		}
		strb_add_back(&strb, ft_substr_guard(str, 0, len), free);
		str += len;
		strb_add_back(&strb, try_expand_value(&str), free);
	}
	return (strb_build(&strb));
}
