/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 17:10:17 by lfabbro           #+#    #+#             */
/*   Updated: 2015/11/30 13:00:41 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	if (!*little)
		return (((char *)big));
	while (big[i] && i < ((int)len))
	{
		while (big[i + k] == little[j] && i + k < ((int)len))
		{
			if (!little[j + 1])
				return (((char *)&big[i + k - j]));
			k++;
			j++;
		}
		j = 0;
		k = 0;
		i++;
	}
	return (0);
}
