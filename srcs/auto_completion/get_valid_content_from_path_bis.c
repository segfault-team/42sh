/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_valid_content_from_path_bis.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 14:28:25 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/07 14:28:25 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		ft_add_list(t_list **first, t_list **ptr, char *str)
{
	if (!*first)
	{
		*first = ft_lstnew(str, ft_strlen(str) + 1);
		*ptr = *first;
	}
	else
	{
		(*ptr)->next = ft_lstnew(str, ft_strlen(str) + 1);
		*ptr = (*ptr)->next;
	}
}

int			ft_countchar(char *str, char c)
{
	int i;

	i = 0;
	while (str && *str)
	{
		if (*str == c)
			++i;
		++str;
	}
	return (i);
}
