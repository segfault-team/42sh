/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 18:34:37 by lfabbro           #+#    #+#             */
/*   Updated: 2016/03/29 15:15:04 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_wstrlen(const wchar_t *wstr)
{
	int			len;
	int			i;

	len = 0;
	i = 0;
	while (wstr[i])
	{
		if (wstr[i] <= 0xFF)
			len += 1;
		else if (wstr[i] <= 0xFFF)
			len += 2;
		else if (wstr[i] <= 0xFFFF)
			len += 3;
		else if (wstr[i] <= 0x10FFFF)
			len += 4;
		++i;
	}
	return (len);
}
