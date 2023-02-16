#include "utils.h"

static void	free_double_ptr(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void	tokenclear(void *token)
{
	if (((t_token *)token)->ud.str)
		free(((t_token *)token)->ud.str);
	if (((t_token *)token)->type == CMD)
	{
		if (((t_token *)token)->ud.cmd_type->args)
			free_double_ptr(((t_token *)token)->ud.cmd_type->args);
		free(((t_token *)token)->ud.cmd_type);
	}
	if (((t_token *)token)->type == REDIR)
	{
		if (((t_token *)token)->ud.redir_type->file)
			free(((t_token *)token)->ud.redir_type->file);
		free(((t_token *)token)->ud.redir_type);
	}
	if (((t_token *)token)->type == PIPE)
		free(((t_token *)token)->ud.pipe_type);
	free(token);
}
