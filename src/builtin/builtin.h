#ifndef BUILTIN_H
# define BUILTIN_H
# include "libft.h"

int	builtin_cd(t_list *argv);
int	builtin_echo(t_list *argv);
int	builtin_env(t_list *argv);
int	builtin_exit(t_list *argv);
int	builtin_export(t_list *argv);
int	builtin_pwd(t_list *argv);
int	builtin_unset(t_list *argv);

#endif