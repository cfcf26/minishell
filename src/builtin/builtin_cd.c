#include <stdio.h>
#include "error.h"
#include "builtin.h"
#include "model.h"
#include "utils.h"

static void	change_pwd(void)
{
	char	*pwd;

	set_env("OLDPWD", data()->pwd);
	free(data()->pwd);
	pwd = getcwd(NULL, 0);
	data()->pwd = pwd;
}

static void	cd_oldpwd(void)
{
	char	*oldpwd;

	oldpwd = get_env("OLDPWD");
	if (oldpwd == NULL)
	{
		print_err("cd", NULL, "OLDPWD not set", 1);
		return ;
	}
	if (chdir(oldpwd))
	{
		free(oldpwd);
		print_err("cd", NULL, NULL, errno);
		return ;
	}
	printf("%s\n", oldpwd);
	free(oldpwd);
}

int	builtin_cd(t_list *argv)
{
	char	*home;

	argv = argv->next;
	if (argv == NULL)
	{
		home = get_env("HOME");
		if (home && chdir(home))
			return (print_err("cd", home, NULL, errno));
		else if (home == NULL)
			return (print_err("cd", NULL, "HOME not set", 1));
		change_pwd();
		free(home);
		return (0);
	}
	else if (ft_strncmp(argv->content, "-", 2) == 0)
		cd_oldpwd();
	else if (chdir(argv->content))
		return (print_err("cd", argv->content, NULL, 1));
	change_pwd();
	return (0);
}
