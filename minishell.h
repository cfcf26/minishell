
#ifndef MINISHELL_H
# define MINISHELL_H

# include "lib/libft/libft.h"
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

# define PIPE_READ 0
# define PIPE_WRITE 1



typedef enum e_token_type
{
	NONE = 0,
	REDIR,
	CMD,
	PIPE,
	WORD,
	VISITED
}	t_token_type;

typedef enum e_redir_type
{
	IN,
	OUT,
	APPEND,
	HEREDOC
}	t_redir_type;

typedef struct s_ms
{
	int		err;
	int		pipe_fd[2];
	int		pipe_last_fd;
	int		backup_stdio_fd[2];
	t_list	*envp;
	t_list	*unlink_lst; //삭제예정 파일 목록
	t_list	*waitpid_lst;
}	t_ms;

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
}	t_cmd;

typedef struct s_red
{
	t_redir_type	redir_type;
	char			*file;
}	t_red;

typedef struct s_pip
{
	int	fd[2];
}	t_pip;

typedef union u_token
{
	t_cmd	*cmd_type;
	t_red	*redir_type;
	t_pip	*pipe_type;
	char	*str;
}	t_utoken;

typedef struct s_token
{
	t_token_type	type;
	t_utoken		ud;
}	t_token;



void		init_signal(void);
void		init_envp(char **envp);
void		execute(t_list *parsed_list);
t_list		*expanding(char *str);
int			parse(char *line, t_list **result);






typedef struct s_func
{
	char	*name;
	void	*func;
}	t_func;

#endif
