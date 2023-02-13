#ifndef UTILS_H
# define UTILS_H
# include "model.h"

int		*intdup(int src);
char	*concat_str(const char *p1, const char *str, const char *p2);
char	**lst2arr(t_list *lst);
t_list	*token_filter(t_list *lst, t_token_type type);
t_token	*token_first(t_list *lst, t_token_type type);
void	destroy_token(t_token *token);
//t_token	*create_token(t_token_type type);
t_token	*to_token(t_list *node);
char	*get_env(char *key);
void	set_env(char *key, char *value);
void	unlink_clear();
void	unlink_add_file(char *str);
void	ft_putstr_fd_line(char *s, int fd);

#endif
