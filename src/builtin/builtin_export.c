#include "utils.h"
#include "builtin.h"

static char	*get_key(char *str)
{
	int	i;

	if (str == NULL || *str == '=')
		return (NULL);
	i = 0;
	while (str[i] && ft_strchr(ENV_CHARSET, str[i]))
		i++;
	if (str[i] != '=')
		return (NULL);
	return (ft_substr_guard(str, 0, i));
}

int	builtin_export(t_list *argv)
{
	char		*key;
	char		*delimiter;

	while (argv)
	{
		argv = argv->next;
		if (argv == NULL)
			continue ;
		key = get_key(argv->content);
		if (key == NULL)
		{
			// TODO: error
			/*
				bash-3.2$ unset !
				bash: unset: `!': not a valid identifier
			*/
			ft_putstr_fd("error\n", 2);
			continue ;
		}
		delimiter = ft_strchr(argv->content, '=');
		if (delimiter == NULL)
		{
			free(key);
			continue ;
		}
		set_env(key, delimiter + 1);
	}
	return (0);
}
