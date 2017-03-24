/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_imaxtoa_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 18:34:51 by lfabbro           #+#    #+#             */
/*   Updated: 2016/12/05 17:24:30 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		get_size(long long value, int base)
{
	int			size;

	size = 0;
	if (value < 0)
	{
		value *= -1;
	}
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

	if ((num = ft_strnew(2)) == NULL)
		return (NULL);
	num[0] = '0';
	num[1] = '\0';
	return (num);
}

static char		*imaxtoa_base_return(long long value, int base, char set)
{
	int			size;
	char		*num;
	long long	uvalue;

	size = get_size(value, base);
	uvalue = value;
	if ((num = ft_strnew(size)) == NULL)
		return (NULL);
	num[size] = '\0';
	if (value < 0)
	{
		uvalue = -value;
	}
	while (uvalue)
	{
		if (uvalue % base < 10)
			num[--size] = "0123456789"[uvalue % base];
		else
			num[--size] = set + ((uvalue % base) - 10);
		uvalue /= base;
	}
	return (num);
}

char			*ft_imaxtoa_base(long long value, int base, char set)
{
	if (base < 2 || base > 16)
		return (NULL);
	if (value == 0)
		return (return_zero());
	return (imaxtoa_base_return(value, base, set));
}
