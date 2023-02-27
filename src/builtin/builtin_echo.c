/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:39:26 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:39:27 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "builtin.h"

static void	print(t_list *argv)
{
	while (argv)
	{
		if (argv->next)
			printf("%s ", (char *)argv->content);
		else
			printf("%s", (char *)argv->content);
		argv = argv->next;
	}
}

static int	is_nextline(t_list **argv)
{
	int		nextline;
	char	*options;

	nextline = 1;
	if (*argv == NULL)
		return (nextline);
	options = (*argv)->content;
	if (*options++ != '-')
		return (nextline);
	if (*options == '\0')
		return (nextline);
	while (*options)
	{
		if (*options != 'n')
			return (1);
		else
			nextline = 0;
		options++;
	}
	(*argv) = (*argv)->next;
	is_nextline(argv);
	return (nextline);
}

int	builtin_echo(t_list *argv)
{
	int	nextline;

	argv = argv->next;
	nextline = is_nextline(&argv);
	print(argv);
	if (nextline)
		printf("\n");
	return (0);
}
