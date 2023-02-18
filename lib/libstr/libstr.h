#ifndef LIBSTR_H
# define LIBSTR_H
# include "libft.h"

// ** string builder **
typedef struct s_strb
{
	t_list	*lst;
	int		len;
}	t_strb;

typedef struct s_strb_item
{
	char	*str;
	void	(*del)(void *);
}	t_strb_item;

void	strb_init(t_strb *b);
void	strb_add_front(t_strb *b, char *str, void (*del)(void *));
void	strb_add_back(t_strb *b, char *str, void (*del)(void *));
void	strb_clear(t_strb *b);
char	*strb_build(t_strb *b);
char	*str_concat(const char *p1, const char *str, const char *p2);

#endif
