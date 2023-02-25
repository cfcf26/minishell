/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_hendler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:38:22 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:38:24 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_signal.h"

void	sigint_handler(int signo)
{
	(void)signo;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_heredoc_handler(int signo)
{
	if (signo == SIGINT)
	{
		data()->parse_err = 1;
		write(2, "\b\b  \b\b\n", 7);
		exit(1);
	}
	else if (signo == SIGQUIT)
	{
		write(2, "\b\b  \b\b", 6);
	}
}
