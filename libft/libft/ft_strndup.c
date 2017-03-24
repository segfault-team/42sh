/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 16:36:57 by lfabbro           #+#    #+#             */
/*   Updated: 2015/12/03 16:40:14 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, size_t n)
{
	size_t	i;
	size_t	slen;
	char	*dup;

	i = -1;
	slen = ft_strlen(src);
	if ((dup = ft_strnew(n)) == NULL)
		return (NULL);
	while (++i < n && i < slen)
		dup[i] = src[i];
	dup[i] = '\0';
	return (dup);
}
