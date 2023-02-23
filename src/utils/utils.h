#ifndef UTILS_H
# define UTILS_H
# include "model.h"

# define ENV_CHARSET "abcdefghijklmnopqrstuvwxyz\
ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_"

char	**lst2arr(t_list *lst);
t_list	*token_filter(t_list *lst, t_token_type type);
t_token	*token_first(t_list *lst, t_token_type type);
void	destroy_token(t_token *token);
t_token	*create_token(t_token_type type);
t_token	*to_token(t_list *node);
t_pip	*to_token_pip(t_list *node);
t_cmd	*to_token_cmd(t_list *node);
t_red	*to_token_red(t_list *node);
void	set_env(char *key, char *value);
char	*get_env(char *key);
char	*get_path(char *str);
int		free_all_return(t_list *tokens, int err_code, t_action_1 del);
void	unlink_clear(void);

#endif
