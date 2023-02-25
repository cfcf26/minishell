/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:37:25 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 01:10:38 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main (int argc, char *argv[], char *envp[])
{
	char	*line;
	t_list	*parsed;

	argc = (int)argc;
	argv = (char **)argv;
	ft_memset(data(), 0, sizeof(t_ms));
	init_signal();
	data()->pwd = getcwd(NULL, 0);
	init_envp(envp);
	init_rl_catch_signals();
	parsed = NULL;
	while (1)
	{
		line = readline(MINISHELL_CONSOLE);
		if (line == NULL)
			break ;
		if (line && ft_strncmp(line, "", 1) != 0)
		{
			if (parse(line, &parsed) == 0)
			{
				execute(parsed);
				ft_lstclear(&parsed, (t_action_1)destroy_token);
			}
			unlink_clear();
			add_history(line);
		}
		free(line);
	}
	printf("exit\n");
	return (0);
}
