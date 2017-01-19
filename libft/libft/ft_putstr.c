/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 18:57:01 by lfabbro           #+#    #+#             */
/*   Updated: 2016/12/17 01:44:14 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** DESCRIPTION:
**     Outputs the string s to the standard output.
**     Returns the number or printed chars.
*/

int			ft_putstr(char const *s)
{
	int		len;

	len = 0;
	if (s)
	{
		len = ft_strlen(s);
		write(1, s, len);
	}
	return ((len));
}
