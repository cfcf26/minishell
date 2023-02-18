#include "model.h"
#include "utils.h"
#include "libstr.h"

t_list	*get_env_node(char *key)
{
	const int	size = ft_strlen(key);
	char		*var;
	t_list		*envps;

	envps = data()->envp;
	while (envps)
	{
		var = (char *)(envps->content);
		if (ft_strncmp(var, key, size) == 0 && var[size] == '=')
			return (envps);
		envps = envps->next;
	}
	return (NULL);
}

static void	ft_lstdel_node(t_list **lst, t_list *node, void (*del)(void *))
{
	t_list	*cursor;
	t_list	*back;

	cursor = *lst;
	if (cursor == node)
	{
		*lst = cursor->next;
		ft_lstdelone(cursor, del);
		return ;
	}
	while (cursor)
	{
		if (cursor == node)
		{
			back->next = cursor->next;
			ft_lstdelone(node, del);
			return ;
		}
		back = cursor;
		cursor = cursor->next;
	}
}

void	set_env(char *key, char *value)
{
	t_list	*env;

	env = get_env_node(key);
	if (value == NULL && env != NULL)
		ft_lstdel_node(&(data()->envp), env, free);
	else if (value != NULL && env == NULL)
	{
		env = ft_lstnew_guard(str_concat(key, "=", value));
		ft_lstadd_front(&(data()->envp), env);
	}
	else if (value != NULL && env != NULL)
	{
		free(env->content);
		env->content = str_concat(key, "=", value);
	}
}
