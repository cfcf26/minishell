#include "minishell.h"

int main (int argc, char *argv[], char *envp[])
{
	char	*line;
	t_list	*parsed;

	ft_memset(data(), 0, sizeof(t_ms));
	init_signal();
	init_envp(envp);
	parsed = NULL;
	while (1)
	{
		line = readline("> ");
		if (parse(line, &parsed) == 0)
		{
			execute(parsed);
			ft_lstclear(parsed, NULL);
		}
		free(line);
	}
	return (0);
}
