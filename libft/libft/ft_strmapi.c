/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 17:20:35 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/21 12:05:48 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** DESCRIPTION:
**     Applies the function f to each character of the string passed
**     as argument by giving its index as first argument to create a
**     “fresh” new string (with malloc(3)) resulting from the successive
**     applications of f.
*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		len;
	char	*new_str;

	i = 0;
	if (s && f)
	{
		len = ft_strlen(s);
		if ((new_str = malloc(sizeof(*s) * len)) == NULL)
			return (NULL);
		while (i < len && s[i])
		{
			new_str[i] = f(i, s[i]);
			i++;
		}
		new_str[i] = '\0';
		return (new_str);
	}
	return (NULL);
}
