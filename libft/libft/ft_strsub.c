/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 11:01:10 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/21 12:14:15 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** DESCRIPTION:
**     Allocates (with malloc(3)) and returns a “fresh” substring
**     from the string given as argument. The substring begins at
**     indexstart and is of size len. If start and len aren’t refering
**     to a valid substring, the behavior is undefined. If the
**     allocation fails, the function returns NULL.
*/

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char		*trun;
	size_t		i;

	i = 0;
	if (s)
	{
		if ((trun = (char *)malloc(sizeof(*trun) * len)) == NULL)
			return (NULL);
		while (i < len)
		{
			trun[i] = s[start + i];
			++i;
		}
		trun[i] = '\0';
		return (trun);
	}
	return (NULL);
}
