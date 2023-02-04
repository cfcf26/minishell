/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekwak <ekwak@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:33:22 by ekwak             #+#    #+#             */
/*   Updated: 2023/02/08 21:41:00 by ekwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

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
				//if (((t_token *)tmp->content)->ud.redir_type->file)
					//free(((t_token *)tmp->content)->ud.redir_type->file);
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
			if (parse(line, &parsed) == 0)
			{
				execute(parsed);
				ft_lstclear(&parsed, NULL);
			}
			add_history(line);
		}
		free(line);
	}
	return (0);
}
