#include "parse.h"

static int	pipes(char *line, t_list **lst, int i)
{
	t_token	*token;
	int		j;

	j = i;
	token = (t_token *)ft_calloc_guard(sizeof(t_token), 1);
	while (line[j] && line[j] == '|')
		j++;
	token->type = PIPE;
	token->ud.str = ft_substr_guard(line, i, j - i);
	ft_lstadd_back(lst, ft_lstnew_guard(token));
	return (j);
}

static int	redirect(char *line, t_list **lst, int i)
{
	t_token	*token;
	int		j;

	j = i;
	token = (t_token *)ft_malloc_guard(sizeof(t_token));
	token->type = REDIR;
	while (line[j] && line[j] == line[i])
		j++;
	token->ud.str = ft_substr_guard(line, i, j - i);
	ft_lstadd_back(lst, ft_lstnew_guard(token));
	return (j);
}

static int	quote(char *line, int *i)
{
	int	j;

	j = *i + 1;
	while (line[j] && line[j] != line[*i])
		j++;
	if (line[j] == '\0')
	{
		data()->parse_err = 258;
		print_err(NULL, NULL, "syntax error", 258);
		return (j);
	}
	return (j);
}

static int	word(char *line, t_list **lst, int i)
{
	int		j;
	char	*str;
	t_token	*token;

	j = i;
	while (line[i] && line[i] != ' ' && line[i] != '|' \
		&& line[i] != '>' && line[i] != '<')
	{
		if (line[i] == '\'' || line[i] == '\"')
			i = quote(line, &i);
		if (data()->parse_err == 258)
			return (i);
		i++;
	}
	str = ft_substr_guard(line, j, i - j);
	token = create_token_word(str);
	ft_lstadd_back(lst, ft_lstnew_guard(token));
	return (i);
}

void	line_to_token(char *line, t_list **result)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else if (line[i] == '|')
			i = pipes(line, result, i);
		else if (line[i] == '>' || line[i] == '<')
			i = redirect(line, result, i);
		else
			i = word(line, result, i);
		if (data()->parse_err)
			return ;
	}
	return ;
}
