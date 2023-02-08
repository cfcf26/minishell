#include "minishell.h"

void	in_quote(char *str, int offset, t_exp_data *str_data)
{
	str_data->quote = check_quote(str_data->quote, str[offset]);
	if (str_data->quote == '\0')
	str_data->len = check_in_quote_len(str, offset, str_data);
	str_data->str = strs_join(str, offset, str_data);
}

void	without_quote(char *str, int offset, t_exp_data *str_data)
{
	if (str[i + 1] == '\0' || \
				(str_data->quote == '\0' && (str[i] == '\'' || str[i] == '\"')))
	{
		str_data->str = strs_join(str, i, str_data);
		str_data->quote = str[i];
	}
}

char	*except_quote(char *str, t_exp_data *str_data)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str_data->quote == '\'' || str_data->quote == '\"')
		{
			in_quote(str, i, str_data);
			i++;
			*str_data = reset_exp_data(str_data, 1);
		}
		else
		{
			without_quote(str, i, str_data);
			i++;
			str_data->len++;
			*str_data = reset_exp_data(str_data, 1);
		}
	}
	return (str_data->str);
}

void	remove_quote(t_list *exp_list, t_exp_data *str_data)
{
	t_list	*head;

	head = exp_list;
	*str_data = reset_exp_data(str_data, 0);
	while (head)
	{
		head->content = except_quote(head->content, str_data);
		head = head->next;
	}
}
