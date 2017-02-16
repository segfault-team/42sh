/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_ctrl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboddez <kboddez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 13:08:16 by kboddez           #+#    #+#             */
/*   Updated: 2017/02/16 10:38:53 by kboddez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	ctrl_up_is_not_on_prompt(t_env *e)
{
	if (TCAPS.nb_line == 2 && TCAPS.nb_col < (int)ft_strlen(e->prompt))
		return (0);
	return (-1);
}

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

	l = TCAPS.nb_read;
	while (l--)
	{
		xputs("le");
		TCAPS.nb_move = 0;
	}
	xputs("cr");
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
//	dprintf(1, "\n\nnb_move
	while (TCAPS.nb_move < TCAPS.nb_read)
		move_right(e);
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
		move_right(e);
		++i;
	}
	while (i > 0 && i != TCAPS.nb_read && e->line[i - 1] != ' ')
	{
		move_right(e);
		++i;
	}
	while (e->line[i] == '-' || e->line[i] == ' ')
	{
		move_right(e);
		++i;
	}
}

/*
 **  INSTRUCTION FOR "Ctrl + ARROW <-" KEYS
 */

void	tcaps_ctrl_mov_left(t_env *e)
{
	int	i;

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
		move_right(e);
		++i;
	}
}

/*
**  INSTRUCTION FOR "Ctrl + ARROW UP/DOWN"
**	ARROW_UP	== 65
**	ARROW_DOWN	== 66
*/

static void	tcaps_ctrl_up_down(t_env *e, char buf[3])
{
	int		line;

	line = WIN_WIDTH;
	tcaps_recalc_pos(e);
	if (buf[2] == ARROW_UP && ctrl_up_is_not_on_prompt(e))
	{
		if (TCAPS.nb_line > 1)
		{
			while (line--)
			{
				xputs("le");
				--TCAPS.nb_move;
			}
			tcaps_recalc_pos(e);
		}
	}
	else if (buf[2] == ARROW_DOWN)
	{
		while (line-- && TCAPS.nb_move < TCAPS.nb_read)
			move_right(e);
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
	else if (tcaps_check_key(buf, 59, 53, 68))
		tcaps_ctrl_mov_left(e);
	else
		tcaps_ctrl_up_down(e, buf);
	tcaps_recalc_pos(e);
}
