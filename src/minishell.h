/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:37:20 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/27 10:49:51 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <readline/readline.h>
# include <readline/history.h>
# include "utils.h"
# include "ft_signal.h"
# define MINISHELL "sushihouse"
# define MINISHELL_CONSOLE "sushihouse> "

void	rl_replace_line(const char *s, int clear_undo);

void	init_envp(char **envp);
int		execute(t_list *parsed_list);
t_list	*expanding(char *str);
int		parse(char *line, t_list **result);

#endif
