/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekwak <ekwak@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:33:22 by ekwak             #+#    #+#             */
/*   Updated: 2023/01/31 18:22:15 by ekwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
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
