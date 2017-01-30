/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:26:39 by lfabbro           #+#    #+#             */
/*   Updated: 2017/01/30 11:26:54 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	CHECK IF THE CURRENT KEY IS
**		THE ONE WE WANT
*/

int		tcaps_check_key(char buf[3], int a, int b, int c)
{
	if (buf[0] == (char)a && buf[1] == (char)b && buf[2] == (char)c)
		return (1);
	return (0);
}

/*
**	CHECK IF THE CURRENT KEY IS
**		PRINTABLE CHAR
*/

int		tcaps_check_read(char buf[3])
{
	if (!buf[1] && !buf[2] && (buf[0] >= 32 && buf[0] < 126))
		return (1);
	return (0);
}
