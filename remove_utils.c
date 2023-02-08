#include "minishell.h"

int	check_in_quote_len(char *str, int offset, t_exp_data *str_data)
{
	while (str[offset] != str_data->quote)
	{
		str_data->len++;
	}
}