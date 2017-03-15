/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_rewrite_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 18:04:57 by lfabbro           #+#    #+#             */
/*   Updated: 2017/03/03 01:32:33 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	sc: save position curosr
**	cr: carriage return (debut de ligne)
**	dm: start delete mode
**	le: left
**	dc: delete one char
**	dl: delete line
**	ce: delete line from cursor
**	ed: end delete mode
**	rc: recover cursor position
*/

int		tcaps_rewrite_line(t_env *e, char *str)
{
	int		l;

	xputs(TGETSTR_SC);
	xputs(TGETSTR_CR);
	xputs(TGETSTR_DM);
	l = TCAPS.nb_read;
	while (--l > 0)
	{
		xputs(TGETSTR_LE);
		xputs(TGETSTR_DC);
	}
	xputs(TGETSTR_DL);
	xputs(TGETSTR_CE);
	xputs(TGETSTR_ED);
	tcaps_prompt(e->prompt);
	tputs(str, 1, dsh_putchar);
	xputs(TGETSTR_RC);
	return (0);
}
