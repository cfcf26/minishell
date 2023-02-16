#ifndef MODEL_H
# define MODEL_H
# include "libft.h"

/******************** core ********************/
typedef struct s_ms
{
	int		err;
	int		parse_err;
	int		pipe_fd[2];
	int		pipe_last_fd;
	int		backup_stdio_fd[2];
	char	*pwd;
	t_list	*envp;
	t_list	*unlink_lst;
	t_list	*waitpid_lst;
}	t_ms;

/******************** token types ********************/
typedef enum e_token_type
{
	NONE = 0,
	REDIR,
	PIPE,
	CMD,
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

/******************** tokens ********************/
typedef struct s_cmd
{
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

t_ms	*data();

#endif
