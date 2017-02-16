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

static void	print_new_cmd_from_history(t_env *e)
{
	ft_printf("%s", e->history[TCAPS.hist_move]);
	TCAPS.nb_read = (int)ft_strlen(e->history[TCAPS.hist_move]);
	TCAPS.nb_move = TCAPS.nb_read;

}

/*
**		MANAGE THE TERMCAPS HISTORY
**		FOR UP ARROW
*/

int		tcaps_history_up(t_env *e)
{
	TCAPS.nb_move = TCAPS.nb_read;
	if (!e->history || !e->history[0])
		return (0);
	if (TCAPS.hist_move == -1)
		TCAPS.hist_move = (int)ft_tablen(e->history);
	if (access(HIST_FILE, F_OK) != -1 && TCAPS.hist_move > 0)
	{
		--TCAPS.hist_move;
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

int		tcaps_history_down(t_env *e)
{
	int	hist_tab_len;

	if (TCAPS.hist_move == -1 || !e->history || !e->history[0])
		return (0);
	hist_tab_len = (int)ft_tablen(e->history);
	clear_cmd(e);
	if (TCAPS.hist_move == hist_tab_len - 1)
	{
		TCAPS.hist_move = -1;
		strfree(&e->line);
		TCAPS.nb_read = 0;
		TCAPS.nb_move = 0;
	}
	else
	{
		++TCAPS.hist_move;
		strfree(&e->line);
		e->line = ft_strdup(e->history[TCAPS.hist_move]);
		print_new_cmd_from_history(e);
	}
	return (1);
}
