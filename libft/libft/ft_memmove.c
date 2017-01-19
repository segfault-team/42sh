/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 18:20:00 by lfabbro           #+#    #+#             */
/*   Updated: 2015/11/30 12:14:19 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*sd;
	unsigned char	*ss;

	if (dst && src)
	{
		sd = (unsigned char *)dst;
		ss = (unsigned char *)src;
		if (dst > src)
		{
			sd += len;
			ss += len;
			while (len--)
				*--sd = *--ss;
		}
		else
			ft_memcpy(dst, src, len);
	}
	return (dst);
}
