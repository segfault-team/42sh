/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_delete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:27:38 by lfabbro           #+#    #+#             */
/*   Updated: 2017/02/01 10:13:23 by kboddez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	INSTRUCTION FOR DELETE KEY
**
**		dm: start delete mode
**		le : move left
**		dc : delete char
**		ed: end delete mode
*/

static void	tcaps_del_end(t_env *e)
{
	char	*res;

	res = tgetstr("dm", NULL);
	tputs(res, 1, dsh_putchar);
	res = tgetstr("le", NULL);
	tputs(res, 1, dsh_putchar);
	if (TCAPS.nb_move)
		--TCAPS.nb_move;
	tcaps_recalc_pos(e);
	if (TCAPS.nb_col == WS_COL - 1)
	{
		res = tgetstr("ce", NULL);
		tputs(res, 1, dsh_putchar);
	}
	res = tgetstr("dc", NULL);
	tputs(res, 1, dsh_putchar);
	--TCAPS.nb_read;
	res = tgetstr("ed", NULL);
	tputs(res, 1, dsh_putchar);
}

void		tcaps_del(t_env *e)
{
	char *res;

	if (TCAPS.nb_move == TCAPS.nb_read)
		tcaps_del_end(e);
	else
	{
		if (!TCAPS.nb_read && e->line)
		{
			free(e->line);
			e->line = NULL;
		}
		res = tgetstr("le", NULL);
		tputs(res, 1, dsh_putchar);
		--TCAPS.nb_read;
		if (TCAPS.nb_move)
			--TCAPS.nb_move;
		tcaps_putstr(e);
	}
}
