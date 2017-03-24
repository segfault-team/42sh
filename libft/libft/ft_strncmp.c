/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 17:26:10 by lfabbro           #+#    #+#             */
/*   Updated: 2015/11/30 13:03:34 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int		i;

	i = 0;
	while (s1[i] == s2[i] && n-- && s1[i] && s2[i])
	{
		i++;
	}
	if (n != 0)
		if (s2[i] != s1[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
	return (0);
}
