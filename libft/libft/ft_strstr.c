/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 16:51:00 by lfabbro           #+#    #+#             */
/*   Updated: 2016/11/28 14:33:08 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!little || !*little)
		return (((char *)big));
	if (big)
	{
		while (*big)
		{
			while (*(big + i) == *(little + j))
			{
				if (!*(little + j + 1))
					return (((char *)&*(big + i - j)));
				i++;
				j++;
			}
			j = 0;
			i = 0;
			++big;
		}
	}
	return (0);
}
