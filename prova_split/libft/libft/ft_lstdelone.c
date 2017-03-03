/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 16:09:55 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/21 11:30:03 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** DESCRIPTION
**     Takes as a parameter a link’s pointer address and frees the
**     memory of the link’s content using the function del given as
**     a parameter, then frees the link’s memory using free(3). The
**     memory of next musnt not be freed under any circumstance.
**     Finally, the pointer to the link that was just freed must be
**     set to NULL (quite similar to the function ft_memdel in the
**     mandatory part).
*/

void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	del((*alst)->content, (*alst)->content_size);
	free((void *)*alst);
	*alst = NULL;
}
