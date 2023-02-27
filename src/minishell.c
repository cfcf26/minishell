/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:37:25 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/27 10:57:52 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init(int argc, char **argv, char **envp)
{
	if (argc != 1)
	{
		ft_putstr_fd("not supported\n", STDERR_FILENO);
		exit(1);
	}
	(void)argv;
	data();
	init_signal();
	init_envp(envp);
	init_rl_catch_signals();
}

static int	check_no_empty_line(char *line)
{
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	if (*line == '\0')
		return (0);
	return (1);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	t_list	*parsed;

	init(argc, argv, envp);
	parsed = NULL;
	while (1)
	{
		line = readline(MINISHELL_CONSOLE);
		if (line == NULL)
			break ;
		if (line && check_no_empty_line(line))
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
