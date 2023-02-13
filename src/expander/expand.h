#ifndef EXPAND_H
# define EXPAND_H
# include "libft.h"
# include "envp.h"

typedef struct s_exp_data
{
	int					len;
	int					key_len;
	char				quote;
	char				*value;
	char				*key;
	char				*str;
}	t_exp_data;

void		remove_quote(t_list *exp_list, t_exp_data *str_data);
t_exp_data	reset_exp_data(t_exp_data *node, int flag);
char		*strs_join(char *str, int offset, t_exp_data *str_data);
char		*expand_env(char *str, int offset, t_exp_data *str_data, \
t_envp_list *list);
char		check_quote(char last_quote, char now_quote);
char		*exception_dollor(char *str, t_exp_data *str_data);
t_list		*split_exp_str(char *str, t_exp_data *str_data);

#endif