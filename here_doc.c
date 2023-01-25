/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juykang <juykang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:30:08 by juykang           #+#    #+#             */
/*   Updated: 2022/12/13 16:28:46 by juykang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*create_random_file(void)
{
	int			fd;
	const char	material[62] = "abcdefghijklmnopqrxtuvwxyz\
ABCDEFGHIJKLMNOPQRXTUVWXYZ0123456789";
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
		tmp[0] = material[(unsigned char)tmp % 62];
		tmp_name = ft_strjoin(file_name, tmp);
		free(file_name);
		file_name = tmp_name;
	}
	close(fd);
	return (file_name);
}

void	fill_tmp_file(int fd, char *limit)
{
	char	*buff;

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
}

char	*make_tmp_infile(char *limit)
{
	char	*file_name;
	int		fd;

	file_name = create_random_file();
	fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		print_error("infile error!");
	fill_tmp_file(fd, limit);
	close(fd);
	return (file_name);
}

t_file	*setting_bonus_file(int count, char **argv)
{
	t_file	*res;

	res = (t_file *)malloc(sizeof(t_file));
	if (!res)
		print_error("malloc error!");
	res->infile = make_tmp_infile(argv[2]);
	res->cmd_cnt = count - 4;
	res->outfile = argv[count - 1];
	res->stdin_fd = 0;
	res->outdin_fd = 0;
	res->read_fd = 0;
	res->here_doc_flag = 1;
	return (res);
}
