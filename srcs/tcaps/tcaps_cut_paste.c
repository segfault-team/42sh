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
	i = TCAPS.nb_move - 1;
	strfree(&e->cut);
	e->cut = ft_strndup(&e->line[i], len);
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
	int	cut_len;

	if (e->cut)
	{
		cut_len = (int)ft_strlen(e->cut);
		xputs("sc");
		clear_cmd(e);
		ft_realloc_insert_str(e, e->cut);
		TCAPS.nb_read = (int)ft_strlen(e->line) + 1;
		TCAPS.nb_move += cut_len - 1;
		xputs("cr");
		ft_putstr(e->prompt);
		ft_putstr(e->line);
		xputs("rc");
		while (cut_len--)
			move_right(e);
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
