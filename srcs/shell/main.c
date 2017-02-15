#include "shell.h"

/*
**	INSTRUCTIONS FOR ENTER KEY
*/

static void		tcaps_enter(t_env *e)
{
	tcaps_ctrl_end(e);
//	ft_putchar('\n');
	TCAPS.hist_move = -1;
	ft_putchar('\n');
	if (e->line && ft_parse_line(e))
		ft_putchar('\n');
	if (!ft_strstr(e->line, "exit"))
		ft_putstr(e->prompt);
	TCAPS.nb_move = 0;
	TCAPS.nb_read = 0;
	if (e->line)
		free(e->line);
	e->line = NULL;
}

/*
**	INSTRUCTION FOR ALL KEY
**	WITH PRINTABLE CHAR
*/

static void		tcaps_manage_printable_char(t_env *e)
{
	if (TCAPS.nb_move == TCAPS.nb_read)
		e->line = ft_realloc_line(e, BUF[0]);
	else
		e->line = ft_realloc_insert_char(e, BUF[0]);
	TCAPS.nb_read = ft_strlen(e->line);
}

static int		tcaps_is_delete_key(t_env *e)
{
	if (e->line && e->buf[0] == 127)
		return (1);
	return (0);
}

int				main(int ac, char **av, char **env)
{
	t_env	e;

	ft_init(&e, ac, av, env);
	ft_banner(&e);
	ft_set_sig_handler();
	while (e.x)
	{
		read(0, e.buf, 3);
		if (ft_check_ctrlc(0))
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
		e.check_remove_tab = 0;
		e.i_mag = 0;
		if (e.tcaps.nb_move < e.tcaps.nb_read)
			e.tcaps.check_move = 1;
	}
	ft_env_free(&e);
	ft_putendl("exit");
	return (e.exit);
}
