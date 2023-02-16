#include "utils.h"
#include "builtin.h"

int	builtin_unset(t_list *argv)
{
	char		*key;

	argv = argv->next;
	while (argv)
	{
		key = argv->content;
		if (ft_iscontain(ENV_CHARSET, key) == 0)
		{
			// TODO: error
			/*
				bash-3.2$ unset !
				bash: unset: `!': not a valid identifier
			*/
			ft_putstr_fd("error", 2);
			continue ;
		}
		set_env(key, NULL);
		argv = argv->next;
	}
	return (0);
}
