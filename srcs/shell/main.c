#include "shell.h"

void			tcaps_prompt(char *prompt)
{
	tputs(GREEN, 1, dsh_putchar);
	tputs(prompt, 1, dsh_putchar);
	tputs(ENDC, 1, dsh_putchar);
}

void			ft_prompt(char *prompt)
{
	ft_putstr(GREEN);
	ft_putstr(prompt);
	ft_putstr(ENDC);
}

/*
**	INSTRUCTIONS FOR ENTER KEY
**	tcaps_ctrl_end moves the cursor to the eol,
**	this avoid writing over multi lines
*/

static void		tcaps_enter(t_env *e)
{
	if (!ft_multiline(e))
		return ;
	tcaps_ctrl_end(e);
	ft_putchar('\n');
	if (e->line && ft_parse_line(e))
		ft_putchar('\n');
	if (e->x)
		tcaps_prompt(e->prompt);
	ft_reset_line(e);
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
		xputs(TGETSTR_LE);
		xputs(TGETSTR_CE);
	}
}

void		tcaps_manage_printable_char(t_env *e)
{
	int		len;
	int		s_move;

	s_move = 0;
	len = NB_READ;
	if (NB_MOVE == NB_READ)
		e->line = ft_realloc_line(e, BUF[0]);
	else
	{
		e->line = ft_realloc_insert_char(e, BUF[0]);
		xputs(TGETSTR_DM);
		while (--len > 0)
		{
			xputs(TGETSTR_LE);
			xputs(TGETSTR_CE);
		}
		tcaps_del_prompt(e);
		tcaps_prompt(e->prompt);
		s_move += ft_putstr(e->line);
		while (s_move-- > NB_MOVE)
			xputs(TGETSTR_LE);
		tcaps_recalc_pos(e);
		if (TCAPS.nb_col == (WIN_WIDTH - 1))
		{
			xputs(TGETSTR_DW);
			xputs(TGETSTR_CR);
		}
		else
			xputs(TGETSTR_ND);
	}
	++NB_MOVE;
	++NB_READ;
}

int		tcaps_is_delete_key(t_env *e)
{
	if (e->line && e->buf[0] == 127 && NB_MOVE > 0)
		return (1);
	return (0);
}

static void		reading_loop(t_env *e)
{
	while (e->x)
	{
		read(0, BUF, 3);
		if (e->check_ctrl_c)
			ft_reset_line(e);
		if (e->check_sigtstp)
			tcaps_init(e);
		tcaps_recalc_pos(e);
		if (!TCAPS.check_move)
			NB_MOVE = NB_READ;
		if (tcaps_is_printable(BUF))
			tcaps_manage_printable_char(e);
		else if (tcaps_is_delete_key(e))
			e->line = ft_realloc_delete_char(e, NB_MOVE - 1);
		if (tcaps_check_key(BUF, 10, 0, 0))
			tcaps_enter(e);
		else
			tcaps(e);
		ft_bzero(&BUF, 3);
		RED_INDEX = 0;
		if (NB_MOVE < NB_READ)
			TCAPS.check_move = 1;
	}
}

/*
** for now we handle ctrl-z, later on we will get rid of that
*/

int				main(__attribute__((__unused__)) int ac,
					 __attribute__((__unused__)) char **av,
					 char **env)
{
	t_env	e;

	env_access(&e);
	ft_init(&e, env);
	ft_banner();
	ft_set_sig_handler();
	ft_prompt(e.prompt);
	reading_loop(&e);
	ft_write_history(&e, O_TRUNC);
	ft_env_free(&e);
	ft_putendl("exit");
	return (e.exit);
}
