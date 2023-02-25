/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:39:04 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:39:05 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "libft.h"
# define PIPE_READ 0
# define PIPE_WRITE 1

int		backup_stdio_fd(void);
int		reload_stdio_fd(void);
int		redir(t_list *redir_lst);
int		is_single_builtin(int use_pipe, t_list *cmd);
int		run(t_list *parsed, int *err);
int		run_builtin(t_list *redir_lst, t_list *cmd);
int		run_process(int use_pipe, t_list *red_lst, t_list *exp, int *pid);
int		reopen(int fd1, int fd2);
char	*get_accessible_file(char *cmd);
char	*get_accessible_path(char *cmd);

#endif
