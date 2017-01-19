/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 15:23:00 by lfabbro           #+#    #+#             */
/*   Updated: 2016/01/16 17:39:45 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char			*dst_ptr;
	char const		*src_ptr;

	dst_ptr = (char*)dst;
	src_ptr = (char const*)src;
	while (n-- && src_ptr && dst_ptr)
		*dst_ptr++ = *src_ptr++;
	return (dst);
}
