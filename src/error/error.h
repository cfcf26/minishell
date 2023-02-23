#ifndef ERROR_H
# define ERROR_H

# include <errno.h>

int	set_err(int err);
int	print_err(char *err1, char *err2, char *message, int err);

#endif