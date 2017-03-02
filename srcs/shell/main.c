#include "shell.h"

/*
**	INSTRUCTIONS FOR ENTER KEY
**	tcaps_ctrl_end moves the cursor to the eol,
**	this avoid writing over multi lines
*/

static void		tcaps_enter(t_env *e)
{
	char 	*tmp;

	if (!ft_multiline(e))
		return ;
	tcaps_ctrl_end(e);
	//if (!e->x)
	ft_putchar('\n');
	if (e->line && ft_parse_line(e))
		ft_putchar('\n');
	if (e->x)
		ft_putstr(e->prompt);
	TCAPS.hist_move = -1;
	TCAPS.nb_move = 0;
	TCAPS.nb_read = 0;
	strfree(&e->line);
	strfree(&MULTI);
}

/*
**	INSTRUCTION FOR ALL KEY
**	WITH PRINTABLE CHAR
*/

static void		tcaps_del_prompt(t_env *e)
{
	int		len;

	len = (int)ft_strlen(e->prompt);
	while (len-- >= 0)
	{
		xputs("le");
		xputs("ce");
	}
}

static void		tcaps_manage_printable_char(t_env *e)
{
	if (TCAPS.nb_move == TCAPS.nb_read)
		e->line = ft_realloc_line(e, BUF[0]);
	else
	{
		int		l = NB_READ;
		int		s_move = 0;

		e->line = ft_realloc_insert_char(e, BUF[0]);
		xputs("dm");
		while (--l > 0)
		{
			xputs("le");
			xputs("ce");
		}
		tcaps_del_prompt(e);
		ft_putstr(e->prompt);
		s_move += ft_putstr(e->line);
		while (s_move-- > NB_MOVE)
			xputs("le");
		tcaps_recalc_pos(e);
		if (TCAPS.nb_col == (WIN_WIDTH - 1))
		{
			xputs("do");
			xputs("cr");
		}
		else
			xputs("nd");
	}
	++NB_MOVE;
	++NB_READ;
}

static int		tcaps_is_delete_key(t_env *e)
{
	if (e->line && e->buf[0] == 127 && TCAPS.nb_move > 0)
		return (1);
	return (0);
}

int				main(int ac, char **av, char **env)
{
	t_env	e;

	env_access(&e);
	ft_init(&e, ac, av, env);
	ft_banner(&e);
	ft_set_sig_handler();
	while (e.x)
	{
		read(0, e.buf, 3);
		if (e.check_ctrl_c)
			ft_reset_line(&e);
		tcaps_recalc_pos(&e);
		if (!e.tcaps.check_move)
			e.tcaps.nb_move = e.tcaps.nb_read;
		if (tcaps_is_printable(e.buf))
			tcaps_manage_printable_char(&e);
		else if (tcaps_is_delete_key(&e))
			e.line = ft_realloc_delete_char(&e);
		if (tcaps_check_key(e.buf, 10, 0, 0))
			tcaps_enter(&e);
		else
			tcaps(&e);
		ft_bzero(&e.buf, 3);
		e.i_mag = 0;
		if (e.tcaps.nb_move < e.tcaps.nb_read)
			e.tcaps.check_move = 1;
	}
	ft_env_free(&e);
	ft_putendl("exit");
	return (e.exit);
}
