/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 15:35:33 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/21 12:07:18 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** DESCRIPTION:
**     Lexicographical comparison between s1 and s2. If the 2
**     strings are identical the function returns 1, or 0 otherwise.
*/

int			ft_strequ(char const *s1, char const *s2)
{
	if (s1 && s2)
	{
		if (!(*s1) || !(*s2))
			return (1);
		while (*s1)
		{
			if (*s1 != *s2)
				return (0);
			++s1;
			++s2;
		}
		if (*s1 != *s2)
			return (0);
		return (1);
	}
	return (0);
}
