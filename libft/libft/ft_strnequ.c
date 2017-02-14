/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 15:35:33 by lfabbro           #+#    #+#             */
/*   Updated: 2016/11/25 17:19:51 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** DESCRIPTION:
**     Lexicographical comparison between s1 and s2 up to n characters
**     or until a ’\0’ is reached. If the 2 strings are identical,
**     the function returns 1, or 0 otherwise
*/

int				ft_strnequ(char const *s1, char const *s2, size_t n)
{
	int		i;

	i = 0;
	if (s1 && s2)
	{
		if (!(s1[i]) || !(s2[i]))
			return (1);
		while (s1[i] && n)
		{
			if (s1[i] != s2[i])
				return (0);
			if (n > 1)
				++i;
			--n;
		}
		if (s1[i] != s2[i] && n == 0)
			return (0);
		return (1);
	}
	return (0);
}
