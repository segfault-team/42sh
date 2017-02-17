/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 16:23:14 by lfabbro           #+#    #+#             */
/*   Updated: 2016/04/16 13:21:36 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*dst_ptr;
	unsigned char	*src_ptr;

	i = 0;
	dst_ptr = (unsigned char*)dst;
	src_ptr = (unsigned char*)src;
	while (i < n)
	{
		dst_ptr[i] = src_ptr[i];
		if (dst_ptr[i] == (unsigned char)c)
			return (&dst_ptr[i + 1]);
		i++;
	}
	return (NULL);
}
