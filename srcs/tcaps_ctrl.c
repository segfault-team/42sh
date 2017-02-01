/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_ctrl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboddez <kboddez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 13:08:16 by kboddez           #+#    #+#             */
/*   Updated: 2017/02/01 14:32:14 by kboddez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**  INSTRUCTION FOR "Ctrl + l" KEYS
**
**  cl: clear active window
**  To do : reset positions after clear && check buffer after ctrl+l
*/

void	tcaps_clear(t_env *e)
{
	xputs("cl");
	ft_putstr(e->prompt);
}

/*
**  INSTRUCTION FOR "Ctrl + a" KEYS || cmd: home
**
**	cr: return at the begining of the line
**	nd: move cursor once on the right
*/

void	tcaps_ctrl_home(t_env *e)
{
	int		i;
	int	l;

	l = TCAPS.nb_line;
	while (--l)
		xputs("up");
	xputs("cr");
	TCAPS.nb_move = 0;
	i = ft_strlen(e->prompt);
	while (i--)
		xputs("nd");
	tcaps_recalc_pos(e);
}

/*
**  INSTRUCTION FOR "Ctrl + e" KEYS || cmd: end
**
**	cr: return at the begining of the line
**	nd: move cursor once on the right
*/

void	tcaps_ctrl_end(t_env *e)
{
	tcaps_recalc_pos(e);
	while (TCAPS.nb_move < TCAPS.nb_read)
	{
		if (TCAPS.nb_col == (WS_COL - 1) && TCAPS.nb_move)
		{
			xputs("do");
			xputs("cr");
		}
		else
			xputs("nd");
		++TCAPS.nb_move;
		tcaps_recalc_pos(e);
	}
}

/*
 **  INSTRUCTION FOR "Ctrl + ARROW ->" KEYS
 */

void	tcaps_ctrl_mov_right(t_env *e)
{
	int		i;

	i = TCAPS.nb_move;
	while ((i > 0 && i != TCAPS.nb_read && e->line[i - 1] == ' ')
			|| (!i && TCAPS.nb_read))
	{
		xputs("nd");
		++TCAPS.nb_move;
		++i;
	}
	while (i > 0 && i != TCAPS.nb_read && e->line[i - 1] != ' ')
	{
		xputs("nd");
		++TCAPS.nb_move;
		++i;
	}
	while (e->line[i] == '-' || e->line[i] == ' ')
	{
		xputs("nd");
		++TCAPS.nb_move;
		++i;
	}
}

/*
 **  INSTRUCTION FOR "Ctrl + ARROW" KEYS
 **
 **	tcaps_check_key(buf, 59, 53, 68)): Ctrl + LEFT  arrow
 **	NOT YET tcaps_check_key(buf, 59, 53, 67)): Ctrl + RIGHT arrow
 */

void	tcaps_ctrl_mov(t_env *e)
{
	int		i;
	char	buf[3];

	read(0, buf, 3);
	if (tcaps_check_key(buf, 59, 53, 67))
		tcaps_ctrl_mov_right(e);
	else
	{
		i = TCAPS.nb_move;
		while (i > 0 && (e->line[i - 1] == ' ' || e->line[i - 1] == '-'))
		{
			xputs("le");
			--TCAPS.nb_move;
			--i;
		}
		while ((i && e->line[i - 1] != ' '))
		{
			xputs("le");
			--TCAPS.nb_move;
			--i;
		}
		while (e->line[i] == '-')
		{
			xputs("nd");
			++TCAPS.nb_move;
			++i;
		}
	}
	tcaps_recalc_pos(e);
}
