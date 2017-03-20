/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleghmar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/18 15:38:05 by aleghmar          #+#    #+#             */
/*   Updated: 2014/11/19 12:07:09 by aleghmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*clst;
	t_list	*nlst;

	clst = *alst;
	while (clst)
	{
		nlst = clst->next;
		del(clst->content, clst->content_size);
		free(clst);
		clst = nlst;
	}
	*alst = NULL;
}
