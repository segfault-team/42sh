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
		if (!e->raw)
		{
			tcaps_del_prompt(e);
			tcaps_prompt(e->prompt);
			s_move += ft_putstr(e->line);
		}
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

/*
** for now we handle ctrl-z, later on we will get rid of that
*/

int				main(int UNUSED(ac), char **UNUSED(av), char **env)
{
	t_env	*e;
	int		ret;

	e = (t_env *)malloc(sizeof(t_env));
	env_access(e);
	e->raw = ft_init(e, env);
	ft_set_sig_handler();
	if (!e->raw)
		ft_prompt(e->prompt);
	while (e->x)
	{
		read_input(e);
		reading(e);
	}
	ft_write_history(e, O_TRUNC);
	ret = e->exit;
	ft_env_free(e);
	if (!e->raw)
		ft_putendl("exit");
	return (ret);
}
