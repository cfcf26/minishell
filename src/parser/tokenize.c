#include "parse.h"

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
		ft_lstadd_back(lst, ft_lstnew(token));
	return (j);
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
		ft_lstadd_back(lst, ft_lstnew(token));
	return (j);
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
	char	*str;
	t_token	*token;

	j = i;
	while (line[i] && line[i] != ' ' && line[i] != '|' \
		&& line[i] != '>' && line[i] != '<')
	{
		if (line[i] == '\'' || line[i] == '\"')
			i = quote(line, &i, err);
		if (*err == 1)
			return (i);
		i++;
	}
	str = ft_substr(line, j, i - j);
	token = create_token(str);
	if (!add_token(lst, token, err))
		return (i);
	return (i);
}

int	line_to_token(char *line, t_list **result)
{
	int		err;
	int		i;

	i = 0;
	err = 0;
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
