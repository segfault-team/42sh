/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlistrat <vlistrat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 18:43:25 by vlistrat          #+#    #+#             */
/*   Updated: 2017/04/28 18:43:25 by vlistrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**		MANAGE THE TERMCAPS HISTORY
**		FOR UP ARROW
*/

int				tcaps_history_up(t_env *e)
{
	int	pos;

	if (!e->history || !e->history[0])
		return (0);
	pos = locate_history(e->history, HIST_MOVE,
			e->line_bkp ? e->line_bkp : e->line, -1);
	if (HIST_MOVE == -1)
	{
		if (e->line_bkp)
			strfree(&e->line_bkp);
		e->line_bkp = e->line ? ft_strdup(e->line) : ft_strdup("");
		HIST_MOVE = (pos) ? pos : 1;
	}
	if (access(HIST_FILE, F_OK) != -1 && HIST_MOVE > 0 && pos >= 0)
	{
		HIST_MOVE = pos;
		clear_cmd(e);
		strfree(&e->line);
		e->line = ft_strdup(e->history[HIST_MOVE]);
		print_new_cmd_from_history(e);
	}
	tcaps_recalc_pos(e);
	return (1);
}

/*
**	MANAGE THE TERMCAPS HISTORY
**	FOR DOWN ARROW
*/

static int		tcaps_history_down_bis(t_env *e, int pos)
{
	if (pos == -1)
	{
		HIST_MOVE = pos;
		strfree(&e->line);
		if (e->line_bkp)
		{
			e->line = ft_strdup(e->line_bkp);
			strfree(&e->line_bkp);
		}
		print_last_cmd(e);
		return (1);
	}
	return (0);
}

int				tcaps_history_down(t_env *e)
{
	int	pos;

	if (HIST_MOVE == -1 || !e->history || !e->history[0])
		return (0);
	pos = locate_history(e->history, HIST_MOVE,
			e->line_bkp ? e->line_bkp : e->line, 1);
	clear_cmd(e);
	if (tcaps_history_down_bis(e, pos))
		return (1);
	else
	{
		HIST_MOVE = pos;
		strfree(&e->line);
		e->line = ft_strdup(e->history[HIST_MOVE]);
		print_new_cmd_from_history(e);
	}
	return (1);
}
