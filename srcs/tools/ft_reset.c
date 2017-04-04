#include "shell.h"

static void	free_hdoc_list(t_env *e)
{
	if (e->hdoc)
		ft_lstdel(&e->hdoc, ft_bzero);
	e->b_hdoc = NULL;
}

int			ft_reset_line(t_env *e)
{
	if (e->raw)
		e->raw -= 1;
	strfree(&e->line);
	strfree(&e->line_bkp);
	strfree(&MULTI);
	free_hdoc_list(e);
	e->tcaps.nb_move = 0;
	e->tcaps.nb_read = 0;
	TCAPS.hist_move = -1;
	e->check_ctrl_c = 0;
	e->hdoc_nb = 0;
	e->quote = '\0';
	return (0);
}
