/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_insert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:30:20 by lfabbro           #+#    #+#             */
/*   Updated: 2017/02/20 10:14:51 by vlistrat         ###   ########.fr       */
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
	xputs("im");
	tputs(&BUF[0], 1, dsh_putchar);
	xputs("ei");
	++TCAPS.nb_move;
	tcaps_recalc_pos(e);
}
