/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 16:39:09 by lfabbro           #+#    #+#             */
/*   Updated: 2016/11/22 16:54:49 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	DESCRIPTION:
**		Trim str from chars x and return the new NULL terminated trimmed string.
*/

static size_t	ft_trim_len(const char *str, char x)
{
	int		i;
	size_t	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != x)
			++len;
		++i;
	}
	return (len);
}

char			*ft_strxtrim(char const *str, char x)
{
	size_t	len;
	char	*trim;
	int		i;
	int		j;

	i = 0;
	j = 0;
	trim = NULL;
	if (str)
	{
		len = ft_trim_len(str, x);
		if ((trim = ft_strnew(len)) == NULL)
			return (NULL);
		while (str[i])
		{
			if (str[i] != x)
				trim[j++] = str[i];
			++i;
		}
		trim[j] = '\0';
	}
	return (trim);
}
