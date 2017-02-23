#include "shell.h"

static void		tcaps_ctrl_k(t_env *e)
{
	int		i;
	int		j;
	char	*tmp;

	i = TCAPS.nb_move - 1;
	j = -1;
	strfree(&e->cut);
	e->cut = ft_strnew(TCAPS.nb_read - TCAPS.nb_move);
	while (e->line[i++])
		e->cut[++j] = e->line[i];
	i = TCAPS.nb_move - 1;
	tmp = ft_strsub(e->line, 0, TCAPS.nb_move);
	strfree(&e->line);
	e->line = tmp;
	xputs("sc");
	xputs("dm");
	while (i++ < TCAPS.nb_read)
	{
		xputs("ce");
		if (i  % (WIN_WIDTH - 1) == 0)
		{
			xputs("do");
			xputs("cr");
		}
		else
			xputs("nd");
	}
	xputs("ed");
	xputs("rc");
	TCAPS.nb_read -= (int)ft_strlen(e->cut);
}

static void		tcaps_ctrl_p(t_env *e)
{
	int		cut_len;
	int		tmp;

	cut_len = 0;
	tmp = 0;
	if (e->cut)
	{
		cut_len = (int)ft_strlen(e->cut);
		ft_realloc_insert_str(e, e->cut);
		xputs("dm");
		tmp = NB_READ;
		while (--tmp + ((int)ft_strlen(e->prompt) + 1) > 0)
		{
			xputs("le");
			xputs("ce");
		}
		NB_READ = (int)ft_strlen(e->line) + 1;
		tmp = NB_READ - (NB_MOVE + cut_len) - 1;
		xputs("cr");
		ft_putstr(e->prompt);
		ft_putstr(e->line);
		NB_MOVE = NB_READ - 1;
		while (tmp--)
		{
			xputs("le");
			--NB_MOVE;
		}
		tcaps_recalc_pos(e);
	}
}

/*
**	CTRL_K	== 11
**	CTRL_P	== 16
*/

void			tcaps_cut_paste(t_env *e)
{
	if (BUF[0] == CTRL_K)
		tcaps_ctrl_k(e);
	else if (BUF[0] == CTRL_P)
		tcaps_ctrl_p(e);
}
