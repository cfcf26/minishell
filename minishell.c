#include "minishell.h"

//컨디 는  종료!
//컨씨 는 줄바꿈!
//컨 역슬레쉬 는  아무것도 하지마!
// void	print_new_line()
// {
// 	printf("\n");
// }

//릭 안나도록 수정해야함!!!!
void	destroy_lst(t_list *lst)
{
	t_list	*tmp;
	int		i;

	while (lst)
	{
		i = 0;
		tmp = lst;
		lst = lst->next;
		if (((t_token *)tmp->content)->ud.cmd_type || \
		((t_token *)tmp->content)->ud.pipe_type || \
		((t_token *)tmp->content)->ud.redir_type)
		{
			if (((t_token *)tmp->content)->type == PIPE)
				free(((t_token *)tmp->content)->ud.pipe_type);
			else if (((t_token *)tmp->content)->type == REDIR)
			{
				free(((t_token *)tmp->content)->ud.redir_type);
			}
			else if (((t_token *)tmp->content)->type == CMD)
			{
				free(((t_token *)tmp->content)->ud.cmd_type->cmd);
				while (((t_token *)tmp->content)->ud.cmd_type->args && \
				((t_token *)tmp->content)->ud.cmd_type->args[i])
					free(((t_token *)tmp->content)->ud.cmd_type->args[i++]);
				if (((t_token *)tmp->content)->ud.cmd_type->args)
					free(((t_token *)tmp->content)->ud.cmd_type->args);
			}
		}
		else
			free(((t_token *)tmp->content)->ud.str);
		free(tmp->content);
		free(tmp);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	t_list	*parsed;

	if (argc == 0 || argv == 0 || envp == 0)
		return (0);
	ft_memset(data(), 0, sizeof(t_ms));
	init_signal();
	//init_envp(envp);
	while (1)
	{
		line = readline("> ");
		if (line && ft_strncmp(line, "", 1) != 0)
		{
			parsed = NULL;
			if (ft_strncmp(line,"",1) != 0)
			{
				if (parse(line, &parsed) == 0)
				{
					execute(parsed);
					ft_lstclear(&parsed, NULL);
				}
			}
			add_history(line);
		}
		if (line == NULL)
			exit(0);
		free(line);
	}
	return (0);
}
