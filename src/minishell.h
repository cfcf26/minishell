/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:37:20 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:37:23 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define MINISHELL "minishell"
# define MINISHELL_CONSOLE "minishell> "

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <signal.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "model.h"
# include "utils.h"
# include "error.h"
# include "ft_signal.h"

void	rl_replace_line(const char *s, int clear_undo);

void	init_envp(char **envp);
int		execute(t_list *parsed_list);
t_list	*expanding(char *str);
int		parse(char *line, t_list **result);

#endif
