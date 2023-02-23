#ifndef BUILTIN_H
# define BUILTIN_H
# include "libft.h"

typedef struct s_func
{
	char	*name;
	void	*func;
}	t_func;

int		builtin_cd(t_list *argv);
int		builtin_echo(t_list *argv);
int		builtin_env(t_list *argv);
int		builtin_exit(t_list *argv);
int		builtin_export(t_list *argv);
int		builtin_pwd(t_list *argv);
int		builtin_unset(t_list *argv);
void	*get_builtin_func(char *cmd);

#endif