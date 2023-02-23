#include "model.h"
#include "builtin.h"
#include "util.h"
#include "error.h"

static int	with_param(t_list *argv)
{
	int		err_code;
	char	*param;

	param = argv->content;
	err_code = ft_atoi(argv->content);
	if (*param == '-')
		param++;
	while (ft_isdigit(*param))
		param++;
	if (*param != 0)
		return (print_err("exit", argv->content, \
		"numeric argument required", 255));
	return (err_code);
}

int	builtin_exit(t_list *argv)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	argv = argv->next;
	if (argv && argv->next == NULL)
		exit(with_param(argv));
	else if (argv && argv->next)
		return (print_err("exit", NULL, "too many arguments", FT_ERROR));
	exit(data()->err);
}
