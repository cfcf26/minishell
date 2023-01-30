#include "minishell.h"

int main (int argc, char *argv[], char *envp[])
{
	char	*line;
	t_tree	*parsed;

	ft_memset(data(), 0, sizeof(t_ms));
	init_signal();
	init_envp(envp);
	while (1)
	{
		line = readline("> ");
		if (parse(line, &parsed))
			continue ;
		execute(parsed);
		free(line);
		free_tree(parsed, NULL);
	}
	return (0);
}
