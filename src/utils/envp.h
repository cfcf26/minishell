#ifndef ENVP_H
# define ENVP_H
# include "libft.h"

typedef struct s_envp_list
{
	int					len;
	char				*key;
	char				*value;
	struct s_envp_list	*next;
}t_envp_list;

t_envp_list	*set_envp_list(char **envp);

#endif