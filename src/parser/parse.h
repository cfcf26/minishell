/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:38:34 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 01:07:08 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include <fcntl.h>
# include "utils.h"
# include "ft_signal.h"
# include "libft.h"
# include "model.h"
# include "minishell.h"
# include "error.h"

# define MALLOC_ERR 1
# define SYNTAX_ERR 3

int		syntaxer(t_list **lst);
char	*heredoc(char *limit);
void	line_to_token(char *line, t_list **result);
int		check_syntax_error(t_list *lst);
t_list	*init_cmd(t_list **lst);
t_list	*init_pipe(t_list **lst);
t_list	*init_redir_lst(t_list **lst);
int		organize_token_list_by_type(t_list **lst);
t_token	*create_token_word(char *str);

#endif
