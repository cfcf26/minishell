#include "model.h"
#include "builtin.h"
#include "util.h"

int	builtin_exit(t_list *argv)
{
	char	*param;
	int		err_code;

	argv = argv->next;
	param = NULL;
	err_code = 0;
	if (argv)
	{
		param = argv->content;
		err_code = ft_atoi(argv->content);
		if (*param == '-')
			param++;
		while (ft_isdigit(*param))
			param++;
		if (*param != 0)
		{
			// TODO: error 출력
			/**
				bash-3.2$ exit 12b
				exit
				bash: exit: 12b: numeric argument required
				yonshin@c5r7s5 minishell % echo $?
			* */
			err_code = 255;
		}
		data()->err = err_code;
	}
	exit(data()->err);
	return (0);
}
