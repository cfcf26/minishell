#include "parse.h"

int	ft_max(int x, int y)
{
	if (x > y)
		return (x);
	else
		return (y);
}

char	*create_random_file(void)
{
	int			fd;
	const char	material[65] = "abcdefghijklmnopqrstuvwxyz\
ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	char		*file_name;
	char		*tmp_name;
	char		tmp[2];

	fd = open("/dev/urandom", O_RDONLY);
	file_name = ft_strdup("/tmp/pipex_tmp");
	tmp[1] = 0;
	while (!access(file_name, F_OK))
	{
		if (ft_strlen(file_name) > 128)
		{
			free(file_name);
			file_name = ft_strdup("/tmp/pipex_tmp");
		}
		read(fd, tmp, 1);
		tmp[0] = material[(unsigned char)tmp[0] % 62];
		tmp_name = ft_strjoin(file_name, tmp);
		free(file_name);
		file_name = tmp_name;
	}
	close(fd);
	return (file_name);
}

void	here_doc_fork_signal(int fd, char *limit)
{//시그널 처리해야함
	int		pid;
	char	*buff;

	pid = fork();
	if (pid == 0)
	{
		while (1)
		{
			write(1, "pipe heredoc> ", 15);
			buff = get_next_line(0);
			if (!buff)
				break ;
			if (ft_strncmp(buff, limit, ft_max(ft_strlen(buff) - 1, \
			ft_strlen(limit))) == 0)
				break ;
			write(fd, buff, ft_strlen(buff));
			free(buff);
		}
		free(buff);
		exit(0);
	}
	waitpid(pid, NULL, 0);
}

char	*heredoc(char *limit)
{
	char	*file_name;
	int		fd;

	file_name = create_random_file();
	fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		printf("infile error!");
	here_doc_fork_signal(fd, limit);
	close(fd);
	ft_lstadd_back(&data()->unlink_lst, ft_lstnew(file_name));
	return (file_name);
}
