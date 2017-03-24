/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 16:13:48 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/21 11:35:14 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** DESCRIPTION:
**    Iterates the list lst and applies the function f to each link.
*/

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	t_list	*tmp;
	t_list	*ret;

	ret = NULL;
	ret = lst;
	while (ret)
	{
		tmp = ret;
		ret = ret->next;
		if (tmp)
			f(tmp);
	}
}
