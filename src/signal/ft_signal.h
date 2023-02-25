/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:38:17 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:38:19 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SIGNAL_H
# define FT_SIGNAL_H
# include <signal.h>
# include "minishell.h"

void	init_signal(void);
void	init_signal_parent(void);
void	init_signal_here_doc(void);
void	init_signal_child(void);
void	init_rl_catch_signals(void);
void	sigint_handler(int signo);
void	sigint_heredoc_handler(int signo);
#endif
