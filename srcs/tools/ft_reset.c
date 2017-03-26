#include "shell.h"

static void free_hdoc_list(t_env *e)
{
	t_hdoc  *tmp;

	tmp = NULL;
	e->hdoc = e->b_hdoc;
	while (e->hdoc)
	{
		if (e->hdoc->content)
			ft_free_tab(e->hdoc->content);
		e->hdoc->content = NULL;
		tmp = e->hdoc;
		e->hdoc = e->hdoc->next;
		free(tmp);
		tmp = NULL;
	}
}

int		ft_reset_line(t_env *e)
{
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
