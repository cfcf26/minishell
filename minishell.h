/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juykang <juykang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:40:45 by juykang           #+#    #+#             */
/*   Updated: 2023/02/08 21:38:34 by juykang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include "./lib/libft/libft.h"

# define PIPE_READ 0
# define PIPE_WRITE 1

typedef enum e_token_type
{
	NONE = 0,
	REDIR,
	PIPE,
	CMD,
	WORD
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
	t_list	*envp;
	t_list	*unlink_lst;
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

typedef struct s_exp_data
{
	int					len;
	int					key_len;
	char				quote;
	char				*value;
	char				*key;
	char				*str;
}	t_exp_data;

typedef struct s_envp_list
{
	int					len;
	char				*key;
	char				*value;
	struct s_envp_list	*next;
}t_envp_list;

void		init_signal(void);
void		init_envp(char **envp);
void		execute(t_list *parsed_list);
//char		*expanding(char *str, char **envp);
t_list		*expanding(char *str, char **envp);
int			parse(char *line, t_list **result);
t_ms		*data();
t_envp_list	*set_envp_list(char **envp);
t_exp_data	reset_exp_data(t_exp_data *node, int flag);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strchr(const char *s, int c);
char		*strs_join(char *str, int offset, t_exp_data *str_data);
char		*expand_env(char *str, int offset, t_exp_data *str_data, \
t_envp_list *list);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *s);
char		check_quote(char last_quote, char now_quote);
char		*exception_dollor(char *str, t_exp_data *str_data);
t_list		*split_exp_str(char *str, t_exp_data *str_data);

#endif
