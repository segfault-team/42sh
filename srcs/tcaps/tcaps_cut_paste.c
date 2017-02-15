#include "shell.h"

static void		tcaps_ctrl_k(t_env *e)
{
	int		i;
	int		j;
	char	*tmp;

	i = TCAPS.nb_move - 1;
	j = -1;
	if (e->cut)
		free(e->cut);
	e->cut = ft_strnew(TCAPS.nb_read - TCAPS.nb_move);
	while (e->line[i++])
		e->cut[++j] = e->line[i];
	i = TCAPS.nb_move - 1;
	tmp = ft_strsub(e->line, 0, TCAPS.nb_move);
	if (e->line)
		free(e->line);
	e->line = tmp;
	xputs("sc");
	xputs("dm");
	while (i++ < TCAPS.nb_read)
	{
		xputs("ce");
		if (i  % (WS_COL - 1) == 0)
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
	int	i;

	if (e->cut)
	{
		i = TCAPS.nb_move - 1;
		ft_realloc_insert_str(e, e->cut);
		TCAPS.nb_move += (int)ft_strlen(e->cut) - 1;
		TCAPS.nb_read = (int)ft_strlen(e->line) - 1;
		tcaps_putstr(e, e->line);
		while (i++ < TCAPS.nb_move)
			if (i  % (WS_COL - 1) == 0)
			{
				xputs("do");
				xputs("cr");
			}
			else
				xputs("nd");
	}
	TCAPS.nb_move++;
	TCAPS.nb_read++;
	tcaps_recalc_pos(e);
}

void			tcaps_cut_paste(t_env *e)
{
	if (BUF[0] == 11)
		tcaps_ctrl_k(e);
	else if (BUF[0] == 16)
		tcaps_ctrl_p(e);
}
