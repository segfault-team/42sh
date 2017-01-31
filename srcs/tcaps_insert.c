/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_insert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:30:20 by lfabbro           #+#    #+#             */
/*   Updated: 2017/01/31 16:50:36 by vlistrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**  INSTRUCTION FOR ALL INSERTION
**		OF VISIBLE CHAR
**
**  im: start insert mode
**  ei: end insert mode
*/

void	tcaps_insert(t_env *e)
{
	char	*res;

	res = tgetstr("im", NULL);
	tputs(res, 1, dsh_putchar);
	tputs(&BUF[0], 1, dsh_putchar);
	res = tgetstr("ei", NULL);
	tputs(res, 1, dsh_putchar);
	++TCAPS.nb_move;
	tcaps_recalc_pos(e);
}
