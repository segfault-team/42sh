#include "shell.h"

int		ft_putstr_color(char *prefix, char *str, char *color)
{
	int		i;

	i = 0;
	ft_putstr_fd(color, 2);
	ft_putstr_fd(prefix, 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(C_RESET, 2);
	return (i);
}

void	ft_print_ext(t_env *e, char *color, char *spaces)
{
	if (color == C_EXEC)
		ft_putchar_fd('*', 2);
	else if (color == C_DIR)
		ft_putchar_fd('/', 2);
	else if (color == C_WHT)
		ft_putchar_fd('/', 2);
	else if (color == C_BLK)
		ft_putchar_fd('%', 2);
	else if (color == C_CHR)
		ft_putchar_fd('%', 2);
	else if (color == C_FIFO)
		ft_putchar_fd(' ', 2);
	else if (color == C_LNK)
		ft_putchar_fd('@', 2);
	else if (color == C_SOCK)
		ft_putchar_fd(' ', 2);
	else
		ft_putchar_fd('?', 2);
	ft_putstr_fd(spaces, 2);
	xputs(e->struct_tputs.me);
	ft_putstr_fd(" ", 2);
}

void	ft_put_file(t_env *e, int i, char *spaces)
{
	if (e->selected >= 0 && e->selected < e->c_match &&
		e->files[i]->name == e->files[e->selected]->name)
	{
		xputs(e->struct_tputs.mr);
		e->printed = e->selected;
		ft_putstr_color(e->prefix, e->files[i]->name, C_RESET);
	}
	else
		ft_putstr_color(e->prefix, e->files[i]->name, e->files[i]->color);
	if (e->files[i]->color != C_RESET)
		ft_print_ext(e, e->files[i]->color, spaces);
	else
	{
		ft_putstr_fd(spaces, 2);
		xputs(e->struct_tputs.me);
		ft_putstr_fd("  ", 2);
	}
}

char	*ft_pick_color(char *perm)
{
	if (perm[0] == '-' && ft_strchr(perm, 'x'))
		return (C_EXEC);
	else if (perm[0] == 'd')
	{
		if (perm[8] == 'w')
		{
			if (ft_strchr(perm, 't'))
				return (C_WHT);
			else
				return (C_WHT);
		}
		return (C_DIR);
	}
	else if (perm[0] == 'b')
		return (C_BLK);
	else if (perm[0] == 'c')
		return (C_CHR);
	else if (perm[0] == 'p')
		return (C_FIFO);
	else if (perm[0] == 'l')
		return (C_LNK);
	else if (perm[0] == 's')
		return (C_SOCK);
	else
		return (C_REG);
}

int		calc_rows(t_env *e)
{
	int x;
	int tmp;

	tmp = e->tcaps.ws.ws_col / (ft_strlen(e->prefix) + 3 + e->total_len);
	tmp = tmp ? tmp : 1;
	x = (e->c_match / tmp) + 1;
	return (x);
}
