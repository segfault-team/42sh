/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_imaxtoa_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 18:34:51 by lfabbro           #+#    #+#             */
/*   Updated: 2016/04/10 15:13:01 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		get_size(long long value, int base)
{
	int			size;

	size = 0;
	while (value)
	{
		value /= base;
		++size;
	}
	return (size);
}

static char		*return_zero(void)
{
	char		*num;

	if ((num = (char *)malloc(sizeof(char) * 2)) == NULL)
		return (NULL);
	num[0] = '0';
	num[1] = '\0';
	return (num);
}

static char		*uimaxtoa_base_return(long long value, int base, char set)
{
	int			size;
	char		*num;

	size = get_size(value, base);
	if ((num = (char*)malloc(sizeof(char) * size)) == NULL)
		return (NULL);
	num[size] = '\0';
	while (value)
	{
		if (value % base < 10)
			num[--size] = "0123456789"[value % base];
		else
			num[--size] = set + ((value % base) - 10);
		value /= base;
	}
	return (num);
}

char			*ft_uimaxtoa_base(long long value, int base, char set)
{
	if (base < 2 || base > 16)
		return (NULL);
	if (value == 0)
		return (return_zero());
	return (uimaxtoa_base_return(value, base, set));
}
