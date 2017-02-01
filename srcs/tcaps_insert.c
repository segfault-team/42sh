/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_insert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:30:20 by lfabbro           #+#    #+#             */
/*   Updated: 2017/02/01 15:52:23 by kboddez          ###   ########.fr       */
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
	move_right(e);
	++TCAPS.nb_move;
	tcaps_putstr(e);
	tcaps_recalc_pos(e);
}
