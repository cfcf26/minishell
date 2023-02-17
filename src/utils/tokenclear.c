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

//void	tokenclear(void *token)
//{
//	if (!token)
//		return ;
//	if (((t_token *)token)->type == WORD || ((t_token *)token)->type == VISITED)
//		free(((t_token *)token)->ud.str);
//	else if (((t_token *)token)->type == CMD)
//	{
//		if (((t_token *)token)->ud.cmd_type->args)
//			free_double_ptr(((t_token *)token)->ud.cmd_type->args);
//		free(((t_token *)token)->ud.cmd_type);
//	}
//	else if (((t_token *)token)->type == REDIR)
//	{
//		if (((t_token *)token)->ud.redir_type->redir_type)
//			free(((t_token *)token)->ud.redir_type->file);
//		free(((t_token *)token)->ud.redir_type);
//	}
//	else if (((t_token *)token)->type == PIPE)
//		free(((t_token *)token)->ud.pipe_type);
//	free(token);
//}
void	tokenclear(void *token)
{
	if (!token)
		return ;
	if (((t_token *)token)->type == WORD)
	{
		if (((t_token *)token)->ud.str != NULL)
			free(((t_token *)token)->ud.str);
	}
	else if (((t_token *)token)->type == CMD)
	{
		if (((t_token *)token)->ud.cmd_type != NULL)
		{
			if (((t_token *)token)->ud.cmd_type->args != NULL)
				free_double_ptr(((t_token *)token)->ud.cmd_type->args);
			free(((t_token *)token)->ud.cmd_type);
		}
	}
	else if (((t_token *)token)->type == REDIR)
	{
		if (((t_token *)token)->ud.redir_type != NULL)
		{
			if (((t_token *)token)->ud.redir_type->file != NULL)
				free(((t_token *)token)->ud.redir_type->file);
			free(((t_token *)token)->ud.redir_type);
		}
	}
	else if (((t_token *)token)->type == PIPE)
	{
		if (((t_token *)token)->ud.pipe_type != NULL)
			free(((t_token *)token)->ud.pipe_type);
	}
	free(token);
}
