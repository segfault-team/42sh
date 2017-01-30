/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_delete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:27:38 by lfabbro           #+#    #+#             */
/*   Updated: 2017/01/30 14:22:24 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
 **	INSTRUCTIONS FOR DELETES KEYS
 **
 **		tcaps_del_bkw : BACKSPACE
 **		tcaps_del_fwd : DELETE
 **
 **		dm: start delete mode
 **		le : move left
 **		nd : move right
 **		dc : delete char
 **		ed: end delete mode
 */

void		tcaps_del_bkw(t_env *e)
{
	char	*res;

	--TCAPS.nb_read;
	res = tgetstr("dm", NULL);
	tputs(res, 1, dsh_putchar);
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

void		tcaps_del_fwd(t_env *e)
{
	char	*res;
	char	buf[3];

	read(0, buf, 3);
	if (tcaps_check_key(buf, 126, 0, 0))
	{
		res = tgetstr("dm", NULL);
		tputs(res, 1, dsh_putchar);
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
}
