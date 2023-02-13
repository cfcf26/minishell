#ifndef MINISHELL_H
#define MINISHELL_H

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

void	init_signal(void);
void	init_envp(char **envp);
void	execute(t_list *parsed_list);
t_list	*expanding(char *str);
int		parse(char *line, t_list **result);

#endif
