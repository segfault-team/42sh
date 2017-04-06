#include "shell.h"

/*
**		Clear line when history ends (comes back at begin).
*/

void	clear_cmd(t_env *e)
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

void	print_new_cmd_from_history(t_env *e)
{
	ft_printf("%s", e->history[TCAPS.hist_move]);
	NB_READ = (int)ft_strlen(e->history[TCAPS.hist_move]);
	NB_MOVE = NB_READ;
}

void	print_last_cmd(t_env *e)
{
	if (e->line)
	{
		ft_printf("%s", e->line);
		NB_READ = (int)ft_strlen(e->line);
		NB_MOVE = NB_READ;
	}
	else
	{
		NB_READ = 0;
		NB_MOVE = 0;
	}
}

int		locate_history(char **history, int c_pos, char *comp, int dir)
{
	int max;
	int	init;

	max = (int)ft_tablen(history);
	init = 0;
	if (c_pos == -1)
	{
		init = 1;
		c_pos = max - 1;
	}
	if (max < (c_pos + 1))
		return (-1);
	while (c_pos >= 0 && c_pos < max && history[c_pos])
	{
		if (!init)
			c_pos += dir;
		if (!comp || (c_pos >= 0 && c_pos < max
			&& history[c_pos] && ft_start_with(history[c_pos], comp)))
			return (c_pos);
		init = 0;
	}
	return (-1);
}
