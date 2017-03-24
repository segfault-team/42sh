/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 16:43:29 by lfabbro           #+#    #+#             */
/*   Updated: 2016/01/17 01:20:53 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, char *src, size_t n)
{
	size_t		i;
	size_t		len;

	i = 0;
	len = ft_strlen(src);
	while (i < n)
	{
		if (i > len)
			dst[i] = '\0';
		else
			dst[i] = src[i];
		i++;
	}
	return (dst);
}
