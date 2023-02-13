#ifndef PARSE_H
# define PARSE_H
# include "libft.h"
# include "model.h"
# include "minishell.h"

# define MALLOC_ERR 1
# define SYNTAX_ERR 3

int				syntaxer(t_list **lst);
char			*heredoc(char *limit);
int				line_to_token(char *line, t_list **result);
int				check_syntax_error(t_list *lst);
t_redir_type	init_redir_type(char *str);
t_list			*init_redir_lst(t_list **lst);
char			**init_args(t_list *lst);
t_list			*init_cmd(t_list **lst);
t_list			*init_pipe(t_list **lst);
//int	parse(t_list **lst, char *line);

#endif
