/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strxchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <lfabbro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 21:50:23 by lfabbro           #+#    #+#             */
/*   Updated: 2016/11/17 22:08:54 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Description:
**		this function returns the address of the x-th char in a string
*/

char		*ft_strxchr(const char *s, char c, int x)
{
	if (s)
	{
		while (*s && x)
		{
			if (*s == (char)c)
				--x;
			if (!x)
				return ((char*)s);
			++s;
		}
		if (c == '\0')
			return ((char*)s);
		return (NULL);
	}
	return (NULL);
}
