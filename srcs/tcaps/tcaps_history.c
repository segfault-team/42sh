#include "shell.h"

/*
**		MANAGE THE TERMCAPS HISTORY
**		FOR UP ARROW
*/

int				tcaps_history_up(t_env *e)
{
	int	pos;

	TCAPS.nb_move = TCAPS.nb_read;
	if (!e->history || !e->history[0])
		return (0);
	pos = locate_history(e->history, TCAPS.hist_move,
			e->line_bkp ? e->line_bkp : e->line, -1);
	if (TCAPS.hist_move == -1)
	{
		if (e->line)
			e->line_bkp = ft_strdup(e->line);
		else
			e->line_bkp = ft_strdup("");
		TCAPS.hist_move = pos;
	}
	if (access(HIST_FILE, F_OK) != -1 && TCAPS.hist_move > 0 && pos >= 0)
	{
		TCAPS.hist_move = pos;
		clear_cmd(e);
		strfree(&e->line);
		e->line = ft_strdup(e->history[TCAPS.hist_move]);
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
		TCAPS.hist_move = pos;
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

	if (TCAPS.hist_move == -1 || !e->history || !e->history[0])
		return (0);
	pos = locate_history(e->history, TCAPS.hist_move,
			e->line_bkp ? e->line_bkp : e->line, 1);
	clear_cmd(e);
	if (tcaps_history_down_bis(e, pos))
		return (1);
	else
	{
		TCAPS.hist_move = pos;
		strfree(&e->line);
		e->line = ft_strdup(e->history[TCAPS.hist_move]);
		print_new_cmd_from_history(e);
	}
	return (1);
}
