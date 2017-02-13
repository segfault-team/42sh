#include "shell.h"

/*
**		Clear line when history ends (comes back at begin).
*/

void		clear_cmd(t_env *e)
{
	tcaps_ctrl_end(e);
	xputs("dm");
	while (--TCAPS.nb_read + ((int)ft_strlen(e->prompt) + 1) > 0)
	{
		xputs("le");
		xputs("ce");
	}
	TCAPS.nb_read = 0;
	xputs("dl");
	xputs("ce");
	xputs("ed");
	tputs(e->prompt, 1, dsh_putchar);
}


/*
**		MANAGE THE TERMCAPS HISTORY
**		FOR UP ARROW
*/

void	tcaps_history_up(t_env *e)
{
	TCAPS.nb_move = TCAPS.nb_read;
	if (TCAPS.hist_move == -1)
		TCAPS.hist_move = (int)ft_tablen(e->history);
	if (e->history && e->history[0] && access(HIST_FILE, F_OK) != -1 &&
				TCAPS.hist_move >= 0)
	{
		clear_cmd(e);
		if (e->line)
			free(e->line);
		e->line = NULL;
		if (e->line)
			free(e->line);
		e->line = ft_strdup(e->history[TCAPS.hist_move]);
		ft_printf("%s", e->history[TCAPS.hist_move]);
		TCAPS.nb_read = (int)ft_strlen(e->history[TCAPS.hist_move]);
		TCAPS.nb_move = TCAPS.nb_read;
	}
	tcaps_recalc_pos(e);
}

/*
 **	MANAGE THE TERMCAPS HISTORY
 **	FOR DOWN ARROW
 */

int		tcaps_history_down(t_env *e)
{
	int	tab_len;
	static int	last_nb_read = 0;

	TCAPS.nb_move = TCAPS.nb_read;
	tab_len = (int)ft_tablen(e->history);
	if (e->history && e->history[0])
	{
		if (TCAPS.hist_move == -1)
		{
			TCAPS.nb_read = last_nb_read;
			xputs("dm");
			while (--TCAPS.nb_read + ((int)ft_strlen(e->prompt) + 1) > 0)
			{
				xputs("le");
				xputs("ce");
			}
			TCAPS.nb_read = 0;
			xputs("dl");
			xputs("ce");
			tputs(e->prompt, 1, dsh_putchar);
			TCAPS.nb_read = 0;
			last_nb_read = 0;
			return (0);
			}
		clear_cmd(e);
		if (TCAPS.hist_move < tab_len)
		{
			TCAPS.nb_read = (int)ft_strlen(e->history[TCAPS.hist_move]);
			TCAPS.nb_move = TCAPS.nb_read;
			ft_printf("%s", e->history[TCAPS.hist_move]);
			if (e->line)
				free(e->line);
			e->line = ft_strdup(e->history[TCAPS.hist_move]);
		}
	}
	if (TCAPS.hist_move == tab_len - 1)
	{
		clear_cmd(e);
		tputs(e->line, 1, dsh_putchar);
		last_nb_read = ft_strlen(e->line);
		if (e->line)
			free(e->line);
		e->line = NULL;
	}
	tcaps_recalc_pos(e);
	return (0);
}
