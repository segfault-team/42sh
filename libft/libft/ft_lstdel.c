/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 16:12:09 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/21 11:32:14 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** DESCRIPTION:
**     Takes as a parameter the adress of a pointer to a link and
**     frees the memory of this link and every successors of that link
**     using the functions del and free(3). Finally the pointer to
**     the link that was just freed must be set to NULL (quite similar
**     to the function ft_memdel from the mandatory part).
*/

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;
	t_list	*ret;

	ret = NULL;
	ret = *alst;
	while (ret)
	{
		tmp = ret;
		ret = ret->next;
		if (tmp)
			ft_lstdelone(&tmp, del);
	}
	*alst = NULL;
}
