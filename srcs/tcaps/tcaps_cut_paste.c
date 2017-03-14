#include "shell.h"

static void	tcaps_ctrl_k(t_env *e)
{
	int		i;
	int		j;
	char	*tmp;

	j = -1;
	if (NB_MOVE >= (int)ft_strlen(e->line))
		return ;
	strfree(&e->cut);
	e->cut = ft_strdup(&e->line[NB_MOVE]);
	i = NB_MOVE;
	tmp = ft_strsub(e->line, 0, NB_MOVE);
	strfree(&e->line);
	e->line = tmp;
	xputs("sc");
	xputs("dm");
	while (i++ <= NB_READ)
	{
		xputs("ce");
		if (i && (i  % (WIN_WIDTH - 1) == 0))
		{
			xputs("do");
			xputs("cr");
		}
		else
			xputs("nd");
	}
	xputs("ed");
	xputs("rc");
	NB_READ -= (int)ft_strlen(e->cut);
}

static void	tcaps_ctrl_p(t_env *e)
{
	int	cut_len;
	int	tmp;

	cut_len = 0;
	tmp = 0;
	if (e->cut)
	{
		xputs("vi");
		cut_len = (int)ft_strlen(e->cut);
		ft_realloc_insert_str(e, e->cut);
		xputs("dm");
		tmp = NB_READ;
		while (--tmp + ((int)ft_strlen(e->prompt) + 1) > 0)
		{
			xputs("le");
			xputs("ce");
		}
		NB_READ = (int)ft_strlen(e->line);
		tmp = NB_READ - (NB_MOVE + cut_len);
		xputs("cr");
		tcaps_prompt(e->prompt);
		ft_putstr(e->line);
		NB_MOVE = NB_READ;
		while (tmp--)
		{
			xputs("le");
			--NB_MOVE;
		}
		tcaps_recalc_pos(e);
		xputs("ve");
	}
}

/*
**CTRL_K== 11
**CTRL_P== 16
*/

void	tcaps_cut_paste(t_env *e)
{
	if (BUF[0] == CTRL_K && NB_READ)
		tcaps_ctrl_k(e);
	else if (BUF[0] == CTRL_P)
		tcaps_ctrl_p(e);
}
