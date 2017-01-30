/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_arrow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:22:32 by lfabbro           #+#    #+#             */
/*   Updated: 2017/01/30 11:38:01 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	INSTRUCTION FOR UP/DOWN
**		ARROW KEYS
**
**	cr: return at the begining of the line
**  cd: clear the line
*/

void	tcaps_history(t_env *e)
{
	char *res;

	res = tgetstr("cr", NULL);
	tputs(res, 1, dsh_putchar);
	res = tgetstr("cd", NULL);
	tputs(res, 1, dsh_putchar);
	ft_putstr(e->prompt);
	if (tcaps_check_key(BUF, 27, 91, 65))
		tcaps_history_up(e);
	else
		tcaps_history_down(e);
}

/*
**	INSTRUCTION FOR RIGHT
**		ARROW KEYS
**
**  nd: move cursor once on the right
*/

void	tcaps_right(t_env *e)
{
	char	*res;

	res = tgetstr("nd", NULL);
	tputs(res, 1, dsh_putchar);
	++TCAPS.nb_move;
}

/*
**	INSTRUCTION FOR LEFT
**		ARROW KEYS
**
**  le: move cursor once on the left
*/

void	tcaps_left(t_env *e)
{
	char	*res;

	res = tgetstr("le", NULL);
	tputs(res, 1, dsh_putchar);
	--TCAPS.nb_move;
}
