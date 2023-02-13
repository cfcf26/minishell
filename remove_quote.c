#include "minishell.h"

void	in_quote(char *str, int offset, t_exp_data *str_data)
{
	str_data->str = strs_join(str, offset, str_data);
	*str_data = reset_exp_data(str_data, 1);
}

void	without_quote(char *str, int offset, t_exp_data *str_data)
{
	str_data->quote = check_quote(str_data->quote, str[offset]);
	str_data->str = strs_join(str, offset, str_data);
	*str_data = reset_exp_data(str_data, 1);
}

char	*except_quote(char *str, t_exp_data *str_data)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str_data->quote == '\'' || str_data->quote == '\"')
		{
			if (str[i] == '\'' || str[i] == '\"')
				str_data->quote = check_quote(str_data->quote, str[i]);
			if (str_data->quote == '0')
				in_quote(str, i, str_data);
			else
				str_data->len++;
		}
		else
		{
			if (str_data->quote == '0' && (str[i] == '\'' || str[i] == '\"'))
				without_quote(str, i, str_data);
			else
				str_data->len++;
		}
	}
	if (str_data->len > 1)
		str_data->str = strs_join(str, i, str_data);
	return (str_data->str);
}

void	remove_quote(t_list *exp_list, t_exp_data *str_data)
{
	*str_data = reset_exp_data(str_data, 0);
	while (exp_list)
	{
		*str_data = reset_exp_data(str_data, 0);
		exp_list->content = except_quote(exp_list->content, str_data);
		exp_list = exp_list->next;
	}
}
