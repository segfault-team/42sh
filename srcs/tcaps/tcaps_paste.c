#include "shell.h"

static int		is_print(char c)
{
	return (c >= 32 && c <= 126);
}

int				is_paste(char *buf)
{
	if (buf && buf[0] && buf[1] && buf[2])
		if (is_print(buf[0]) && is_print(buf[1]) && (is_print(buf[2]) || buf[2] == 0))
			return (1);
	return (0);
}

int				tcaps_paste(t_env *e, char *buf)
{
	int		i;

	i = -1;
	xputs("im");
//	ft_printf("b: %c.%c.%c\n", buf[0], buf[1], buf[2]);
	while (buf[++i] && i < 3)
	{
		if (is_print(buf[i]))
		{
			ft_putchar_fd(buf[i], 1);
			e->line = ft_realloc_line(e, buf[i]);
			++NB_MOVE;
			++NB_READ;
		}
	}
	xputs("ei");
	tcaps_recalc_pos(e);
	return (i);
}

