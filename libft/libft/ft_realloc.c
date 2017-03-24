/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <lfabbro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/15 18:40:14 by lfabbro           #+#    #+#             */
/*   Updated: 2016/01/28 12:50:33 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_realloc(void *ptr, size_t size)
{
	void		*dup;

	dup = ft_memalloc(size);
	if (ptr)
	{
		if (dup)
			ft_memcpy(dup, ptr, size);
		ft_memdel(&ptr);
	}
	return (dup);
}
