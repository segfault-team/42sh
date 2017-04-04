#include "shell.h"

/*
**		Clear line when history ends (comes back at begin).
*/

void			clear_cmd(t_env *e)
{
	tcaps_ctrl_end(e);
	xputs(TGETSTR_DM);
	while (--TCAPS.nb_read + ((int)ft_strlen(e->prompt) + 1) > 0)
	{
		xputs(TGETSTR_LE);
		xputs(TGETSTR_CE);
	}
	TCAPS.nb_read = 0;
	xputs(TGETSTR_DL);
	xputs(TGETSTR_CE);
	xputs(TGETSTR_ED);
	ft_prompt(e->prompt);
}

static void		print_new_cmd_from_history(t_env *e)
{
	ft_printf("%s", e->history[TCAPS.hist_move]);
	TCAPS.nb_read = (int)ft_strlen(e->history[TCAPS.hist_move]);
	TCAPS.nb_move = TCAPS.nb_read;
}

static void		print_last_cmd(t_env *e)
{
	if (e->line)
	{
		ft_printf("%s", e->line);
		TCAPS.nb_read = (int)ft_strlen(e->line);
		TCAPS.nb_move = TCAPS.nb_read;
	}
	else
	{
		TCAPS.nb_read = 0;
		TCAPS.nb_move = 0;
	}
}


static int		locate_history(char **history, int c_pos, char *comp, int dir)
{
	int max;

	max = (int)ft_tablen(history);
	if (c_pos == -1)
		c_pos = max - 1;
	if (max < (c_pos + 1))
		return (-1);
	while (history[c_pos] && c_pos && c_pos < max)
	{
		c_pos += dir;
		if (!comp || (history[c_pos] && ft_start_with(history[c_pos], comp)))
			return (c_pos);
	}
	return (-1);
}

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
	pos = locate_history(e->history, TCAPS.hist_move, e->line_bkp ? e->line_bkp : e->line, -1);
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

int				tcaps_history_down(t_env *e)
{
	int	pos;

	if (TCAPS.hist_move == -1 || !e->history || !e->history[0])
		return (0);
	pos = locate_history(e->history, TCAPS.hist_move, e->line_bkp ? e->line_bkp : e->line , 1);
	clear_cmd(e);
	if (pos == - 1)
	{
		TCAPS.hist_move = pos;
		strfree(&e->line);
		if (e->line_bkp)
		{
			e->line = ft_strdup(e->line_bkp);
			strfree(&e->line_bkp);
		}
		print_last_cmd(e);
	}
	else
	{
		TCAPS.hist_move = pos;
		strfree(&e->line);
		e->line = ft_strdup(e->history[TCAPS.hist_move]);
		print_new_cmd_from_history(e);
	}
	return (1);
}
