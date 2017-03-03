/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 15:36:47 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/21 11:41:04 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** DESCRIPTION:
**     Allocates (with malloc(3)) and returns a “fresh” memory
**     area. The memory allocated is initialized to 0. If the allocation
**     fails, the function returns NULL.
*/

void	*ft_memalloc(size_t size)
{
	void	*space;

	space = NULL;
	if (size == 0 || (space = malloc(size)) == NULL)
		return (NULL);
	ft_memset(space, 0, size);
	return (space);
}
