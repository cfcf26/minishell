#include "minishell.h"
// TODO: ekwak
// 파싱중 에러가 발생하면 함수 내에서 출력하고 끝내야합니다. 
// 메인 함수에서 에러를 출력하는 함수는 별도로 만들지 않았습니다.
int	ms_lstadd_back(t_list **lst, void *content)
{
	t_list	*new;
	t_list	*last;

	new = ft_lstnew(content);
	if (new == NULL)
		return (1);
	if (*lst == NULL)
	{
		*lst = new;
		return (0);
	}
	ft_lstlast(*lst)->next = new;
	return (0);
}

static int	pipes(char *line, t_list **lst, int i, int *err)
{
	t_token	*token;
	int		j;

	j = i;
	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
	{
		*err = 1;
		return (i);
	}
	while (line[j] && line[j] == '|')
		j++;
	token->type = PIPE;
	token->ud.str = ft_substr(line, i, j - i);
	if (token->ud.pipe_type == NULL)
	{
		*err = 1;
		free(token);
	}
	else
		*err = ms_lstadd_back(lst, token);
	return (j + 1);
}

static int	redirect(char *line, t_list **lst, int i, int *err)
{
	t_token	*token;
	int		j;

	j = i;
	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
	{
		*err = 1;
		return (i);
	}
	token->type = REDIR;
	while (line[j] && line[j] == line[i])
		j++;
	token->ud.str = ft_substr(line, i, j - i);
	if (token->ud.str == NULL)
	{
		*err = 1;
		free(token);
	}
	else
		*err = ms_lstadd_back(lst, token);
	return (j + 1);
}

static int	quote(char *line, int *i, int *err)
{
	int	j;

	j = *i + 1;
	while (line[j] && line[j] != line[*i])
		j++;
	if (line[j] == '\0')
	{
		*err = 1;
		return (j);
	}
	return (j);
}

static int	word(char *line, t_list **lst, int i, int *err)
{
	int		j;
	t_token	*token;

	j = i;
	while (line[i] && line[i] != ' ' && \
		line[i] != '|' && line[i] != '>' && line[i] != '<')
	{
		if (line[i] == '\'' || line[i] == '\"')
			i = quote(line, &i, err);
		if (*err == 1)
			return (i);
		i++;
	}
	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
	{
		*err = 1;
		return (i);
	}
	token->type = WORD;
	token->ud.str = ft_substr(line, j, i - j);
	if (token->ud.str == NULL)
	{
		*err = 1;
		free(token);
	}
	else
		*err = ms_lstadd_back(lst, token);
	return (i);
}

int	line_to_token(char *line, t_list **result)
{
	int		err;
	t_list	*lst;
	int		i;

	i = 0;
	err = 0;
	lst = NULL;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else if (line[i] == '|')
			i = pipes(line, result, i, &err);
		else if (line[i] == '>' || line[i] == '<')
			i = redirect(line, result, i, &err);
		else
			i = word(line, result, i, &err);
		if (err != 0)
			break ;
	}
	return (err);
}

void	lstprint(t_list *lst)
{
	t_token	*tmp;

	while (lst)
	{
		tmp = (t_token *)lst->content;
		printf("type: %d\n", tmp->type);
		if (tmp->type == CMD)
		{
			printf(" %s\n", tmp->ud.cmd_type->args[0]);
			printf(" %s\n", tmp->ud.cmd_type->args[1]);
		}
		lst = lst->next;
	}
}

void	tokenclear(void *token)
{
	if (((t_token *)token)->ud.str)
		free(((t_token *)token)->ud.str);
	free(token);
} 

/// @brief 쉘 명령어를 담은 문자열을 실행 가능한 형태의 파싱리스트로 변환합니다.
/// @param line 쉘 명령어를 담은 문자열
/// @param result 파싱 결과
/// @return 파싱에 실패한 경우 0이 아닌 값을 리턴
int	parse(char *line, t_list **result)
{	
	int	err;

	err = line_to_token(line, result);
	if (err != 0)
		ft_lstclear(result, tokenclear);
	err = syntaxer(result);
	if (err == SYNTAX_ERR)
		printf("syntax error\n");
	//syntaxer(result, &err);
	lstprint(*result);
	//ft_lstclear(result, tokenclear);
	
	return (err);
}
