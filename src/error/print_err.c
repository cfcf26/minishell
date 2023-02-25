/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:39:11 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:39:12 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "minishell.h"

static void	print_two(char *str1, char *str2)
{
	if (str1)
		ft_putstr_fd(str1, STDERR_FILENO);
	if (str2)
		ft_putstr_fd(str2, STDERR_FILENO);
}

static int	print_message_or_perror(char *str, char *message, int err)
{
	if (message == NULL)
	{
		perror(str);
		return (err);
	}
	print_two(str, ": ");
	print_two(message, "\n");
	return (err);
}

int	print_err(char *err1, char *err2, char *message, int err)
{
	if (err)
		data()->err = err;
	if (err1 == NULL && err2 == NULL)
		return (print_message_or_perror(MINISHELL, message, err));
	print_two(MINISHELL, ": ");
	if (err1 == NULL)
		return (print_message_or_perror(err2, message, err));
	if (err2 == NULL)
		return (print_message_or_perror(err1, message, err));
	else
	{
		print_two(err1, ": ");
		return (print_message_or_perror(err2, message, err));
	}
	return (err);
}
