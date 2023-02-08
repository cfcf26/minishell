#include "minishell.h"

char	*split_str(char *str, int offset, t_exp_data *str_data)
{
	char	quote;
	int		len;

	len = 0;
	while (str[offset + len] && \
	(quote || ft_strchr(" \t\n\0|&;()", str[offset + len]) == 0))
	{
		if (quote == 0 && \
		(str[offset + len] == '\'' || str[offset + len] == '\"'))
			quote = str[offset + len];
		else if (quote == '\'' && str[offset + len] == '\'')
			quote = 0;
		else if (quote == '\"' && str[offset + len] == '\"')
			quote = 0;
		len++;
	}
	if (len == 0)
		return (NULL);
	else
	{
		str_data->len = len;
		return (ft_substr(str, offset, len));
	}
}

t_list	*split_exp_str(char *str, t_exp_data *str_data)
{
	t_list	*node;
	t_list	*head;
	int		i;

	i = 0;
	head = ft_lstnew(NULL);
	*str_data = reset_exp_data(str_data, 0);
	while (str[i])
	{
		str_data->str = split_str(str, i, str_data);
		if (str_data->str != NULL)
		{
			node = ft_lstnew(str_data->str);
			ft_lstadd_back(&head, node);
		}
		i += str_data->len;
		*str_data = reset_exp_data(str_data, 0);
	}
	return (head);
}


int export(t_list *envp)
{
	// split_str(envp->content, "=")
}
