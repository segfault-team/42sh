#include "shell.h"

/*
**	INSTRUCTIONS FOR ENTER KEY
**	tcaps_ctrl_end moves the cursor to the eol,
**	this avoid writing over multi lines
*/

static void		tcaps_enter(t_env *e)
{
/*	if (!ft_multiline(e))
		return ;
	else if (!e->hdoc_words && !ft_heredoc(e))
		return ;
	if (e->hdoc_nb && store_heredoc(e))
		return ;
*/	tcaps_ctrl_end(e);
	if (e->line)
		parse_command(e);
	if (!e->raw)
		ft_putchar('\n');
	if (e->line && ft_parse_line(e) && ft_strcmp(e->line, "exit"))
		ft_putchar('\n');
	if (e->x && !e->raw)
		ft_prompt(e->prompt);
	ft_reset_line(e);
}

int				reading(t_env *e)
{
	if (e->check_ctrl_c)
		ft_reset_line(e);
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
	return (0);
}

static void		raw_read(t_env *e, char *buf)
{
	int ret;

	if (e->x)
	{
		ret = read(0, buf, 1);
		if (ret == -1 || ret == 0)
			e->x = 0;
	}
}

void			read_input(t_env *e)
{
	int		count;
	char	c;

	raw_read(e, BUF);
	if (BUF[0] == 27)
		raw_read(e, &BUF[1]);
	if (BUF[1] == 91)
		raw_read(e, &BUF[2]);
	if (BUF[1] >= '0' && BUF[1] <= '9')
	{
		count = 0;
		c = BUF[1];
		while (c >= '0' && c <= '9' && count < 3000)
		{
			count = 10 * count + (c - '0');
			raw_read(e, &c);
		}
		while (count--)
		{
			BUF[0] = c;
			BUF[1] = '\0';
			reading(e);
		}
		ft_bzero(&BUF, 3);
	}
}
