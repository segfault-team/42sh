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

static void		move_nb_char_prompt(char *str)
{
	int	len;

	len = (int)ft_strlen(str);
	while (len--)
		xputs("nd");
}

static void		tcaps_ctrl_p(t_env *e)
{
	int	cut_len;

	if (e->cut)
	{
		cut_len = (int)ft_strlen(e->cut);
		xputs("sc");
		clear_cmd(e);
		ft_realloc_insert_str(e, e->cut);
		TCAPS.nb_read = (int)ft_strlen(e->line);
		TCAPS.nb_move += cut_len - 1;
		xputs("cr");
		if (TCAPS.nb_col > (int)ft_strlen(e->prompt))
			ft_putstr(e->prompt);
		else
			move_nb_char_prompt(e->prompt);
		ft_putstr(e->line);
		xputs("rc");
		while (cut_len--)
			move_right(e);
	}
	TCAPS.nb_move++;
	TCAPS.nb_read++;
	tcaps_recalc_pos(e);
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
