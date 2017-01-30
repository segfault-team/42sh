/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_delete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:27:38 by lfabbro           #+#    #+#             */
/*   Updated: 2017/01/30 11:27:51 by lfabbro          ###   ########.fr       */
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
	if (TCAPS.nb_col == 0 && TCAPS.nb_line != 1)
	  {
	    //	    if (TCAPS.nb_col == 1)
	    // TCAPS.nb_col += ft_strlen(e->prompt);
	    res = tgetstr("dc", NULL);
	    tputs(res, 1, dsh_putchar);
	  }
	else
	  ft_printf("%d | %d\n", TCAPS.nb_col, WS_COL);
	--TCAPS.nb_read;
	res = tgetstr("le", NULL);
	tputs(res, 1, dsh_putchar);
	if (TCAPS.nb_move)
		--TCAPS.nb_move;
	res = tgetstr("dc", NULL);
	tputs(res, 1, dsh_putchar);
	res = tgetstr("ed", NULL);
	tputs(res, 1, dsh_putchar);
	if (!TCAPS.nb_read && e->line)
	{
		free(e->line);
		e->line = NULL;
	}
}
