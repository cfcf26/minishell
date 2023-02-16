#ifndef FT_SIGNAL_H
# define FT_SIGNAL_H
# include <signal.h>
# include "minishell.h"

void	init_signal(void);
void	init_signal_parent(void);
void	init_signal_here_doc(void);
void	init_signal_child(void);
#endif