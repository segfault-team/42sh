#include "shell.h"

/*
 *
 *	sc : save the current cursor position
 *	dm : enter delete mode
 *	ce : clear from the cursor to the end of the line
 *	do : move cursor vertically down (DO n lines)
 *	cr : move the cursor to the beginning of the line it is on
 *	nd : move the cursor right one column (!!UB when cursor is at the right margin)
 *	ed : end delete mode
 *	rc : restore the last saved cursor position
 *
 */

static void		tcaps_ctrl_k(t_env *e)
{
	int		i;
	size_t	len;
	char	*tmp;

	if (!e->line || (len = ft_strlen(e->line) - (size_t)TCAPS.nb_move) <= 0)
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
	if (BUF[0] == CTRL_K && NB_READ)
		tcaps_ctrl_k(e);
	else if (BUF[0] == CTRL_P)
		tcaps_ctrl_p(e);
}
