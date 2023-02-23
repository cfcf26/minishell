#include "builtin.h"

void	*get_builtin_func(char *cmd)
{
	static const t_func	built[] = {
	{"echo", builtin_echo},
	{"cd", builtin_cd},
	{"pwd", builtin_pwd},
	{"export", builtin_export},
	{"unset", builtin_unset},
	{"env", builtin_env},
	{"exit", builtin_exit},
	{NULL, NULL}
	};
	int					i;

	if (cmd == NULL)
		return (NULL);
	i = -1;
	while (built[++i].name)
		if (ft_strncmp(cmd, built[i].name, ft_strlen(built[i].name) + 1) == 0)
			return (built[i].func);
	return (NULL);
}
