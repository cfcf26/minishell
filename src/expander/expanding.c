/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:38:43 by yonshin           #+#    #+#             */
/*   Updated: 2023/02/26 00:38:44 by yonshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libstr.h"
#include "utils.h"
#include "expanding.h"

t_list	*expanding(char *str)
{
	t_list	*res;
	char	*fixed;

	fixed = expand_all(str);
	res = remove_quote(fixed);
	free(fixed);
	return (res);
}
