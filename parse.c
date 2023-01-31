#include "minishell.h"
// TODO: ekwak
// 파싱중 에러가 발생하면 함수 내에서 출력하고 끝내야합니다. 
// 메인 함수에서 에러를 출력하는 함수는 별도로 만들지 않았습니다.

static int	quote(char *line, int i, int *err)
{
	int	j;

	j = i + 1;
	while (line[j] && line[j] != line[i])
		j++;
	if (line[j] == '\0')
	{
		*err = 1;
		return (j);
	}
	return (j);
}

static int	pipes(char *line, t_list **lst, int i, int *err)
{
	t_token	*token;
	t_list	*new_node;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
	{
		*err = 1;
		return (i);
	}
	token->type = PIPE;
	token->ud.str = ft_substr(line, i, 1);
	if (token->ud.str == NULL)
		*err = 1;
	
	ft_lstadd_back(lst, ft_lstnew(token));
	return (i + 1);
}

static int	redirect(char *line, t_list **lst, int i, int *err)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
	{
		*err = 1;
		return (i);
	}
	token->data.word = ft_substr(line, i, 1);
	token->type = REDIR;
	ft_lstadd_back(lst, ft_lstnew(token));
	return (i + 1);
}

static int	word(char *line, t_list **lst, int i, int *err)
{
	int		j;
	t_token	*token;

	j = i;
	while (line[j] && line[j] != ' ' && \
		line[j] != '|' && line[j] != '>' && line[j] != '<')
	{
		if (line[j] == '\'' || line[j] == '\"')
			j = quote(line, j, err);
		if (*err == 1)
			return (j);
		j++;
	}
	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
	{
		*err = 1;
		return (j);
	}
	token->data.word = ft_substr(line, i, j - i);
	token->type = WORD;
	ft_lstadd_back(lst, ft_lstnew(token));
	return (j);
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
		else if (line[i] == '>')
			i = redirect(line, result, i, &err);
		else if (line[i] == '<')
			i = redirect(line, result, i, &err);
		else
			i = word(line, result, i, &err);
		if (err != 0)
			break ;
	}
	return (err);
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
		free_lst();
	return (err);
}
