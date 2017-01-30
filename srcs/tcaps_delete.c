/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_delete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:27:38 by lfabbro           #+#    #+#             */
/*   Updated: 2017/01/30 17:25:22 by kboddez          ###   ########.fr       */
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

void	tcaps_del(t_env *e)
{
	char *res;

	res = tgetstr("dm", NULL);
	tputs(res, 1, dsh_putchar);
	res = tgetstr("le", NULL);
	tputs(res, 1, dsh_putchar);
	res = tgetstr("dc", NULL);
	tputs(res, 1, dsh_putchar);
//	  ft_printf("%d | %d\n", TCAPS.nb_col, WS_COL);
	res = tgetstr("ed", NULL);
	tputs(res, 1, dsh_putchar);
	--TCAPS.nb_read;
	if (TCAPS.nb_move)
		--TCAPS.nb_move;
	if (!TCAPS.nb_read && e->line)
	{
		free(e->line);
		e->line = NULL;
	}
}
