/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 14:29:54 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/07 14:29:54 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	CHECK IF THE CURRENT KEY IS
**		THE ONE WE WANT
*/

int		tcaps_check_key(char buf[3], int k0, int k1, int k2)
{
	if (buf[0] == (char)k0 && buf[1] == (char)k1 && buf[2] == (char)k2)
		return (1);
	return (0);
}

/*
**	CHECK IF THE CURRENT KEY IS
**		PRINTABLE CHAR
*/

int		tcaps_is_printable(char buf[3])
{
	if (buf[0] >= ' ' && buf[0] <= '~')
		return (1);
	return (0);
}
