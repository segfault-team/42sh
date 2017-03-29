#include "shell.h"

int		write_line(t_env *e, int i, int x, char *spaces)
{
	int len;
	int moar;

	moar = 0;
	while (i < e->c_match)
	{
		moar = ft_strlen(e->files[i]->name) > e->tcaps.ws.ws_col ?
			moar + 1 : moar;
		len = e->total_len - ft_strlen(e->files[i]->name);
		if ((i + 4) <= e->c_match)
			spaces[0] = ' ';
		spaces[len] = '\0';
		if (ft_strlen(e->files[i]->name) >= e->tcaps.ws.ws_col)
			spaces[0] = '\0';
		ft_put_file(e, i, spaces);
		spaces[len] = ' ';
		i += x;
	}
	return (moar);
}

void	ft_putstr_spec(t_env *e, char *str)
{
	int tmp;

	tmp = NB_MOVE;
	ft_putstr(str);
	NB_MOVE = ft_strlen(str);
	while (NB_MOVE--)
		xputs(TGETSTR_LE);
	NB_MOVE = tmp;
}

void	actual_print(t_env *e, int i, int moar)
{
	char	*tmp;

	tmp = ft_strnew(e->total_len + 4);
	tmp = ft_memset(tmp, ' ', e->total_len + 2);
	xputs(e->struct_tputs.cd);
	while (i < e->row && (i - e->start) < e->tcaps.ws.ws_row - 1 - moar)
	{
		putchar('\n');
		moar += write_line(e, i, e->row, tmp);
		i++;
	}
	ft_strdel(&tmp);
	while ((i + moar) - e->start)
	{
		xputs(e->struct_tputs.up);
		i--;
	}
	i = NB_MOVE;
	tcaps_ctrl_home(e);
	while (NB_MOVE < i)
		move_right(e);
}

void	pre_print(t_env *e)
{
	e->printed = -1;
	e->row = calc_rows(e);
	actual_print(e, e->start, 0);
	if (e->selected >= 0)
		ft_putstr(e->files[e->selected]->name);
	xputs(e->struct_tputs.ce);
	ft_putstr_spec(e, &e->line[NB_MOVE]);
	if (e->printed < 0 && e->selected >= 0)
	{
		e->start = e->start + 1 < e->row ? e->start + 1 : 0;
		pre_print(e);
	}
}

void	print_auto_completion(t_env *e, char *arg, char *path, char **content)
{
	if (path)
	{
		e->path = ft_strjoin(path, "/");
		ft_strdel(&path);
		e->prefix = arg;
		e->files = (t_file **)malloc((ft_tablen(content) + 1) * sizeof(t_file*));
		e->files[ft_tablen(content)] = NULL;
		ft_fill_files(content, e);
		ft_free_tab(content);
	}
	if (e->c_match == 1)
	{
		e->selected = 0;
		valid_selection(e);
	}
	pre_print(e);
}

void	reset_autocomp(t_env *e)
{
	int i;

	i = 0;
	while (e->files && e->files[i])
	{
		ft_strdel(&e->files[i]->name);
		ft_memdel((void **)&e->files[i]);
		i++;
	}
	ft_memdel((void **)&e->files);
	ft_strdel(&e->path);
	ft_strdel(&e->prefix);
	e->selected = -42;
	e->files = NULL;
	e->path = NULL;
	e->prefix = NULL;
	e->total_len = 0;
	e->start = 0;
	e->c_match = 0;
}

void	insert_after_comp(t_env *e)
{
	if (e->buf[0] != 10 && e->buf[0] != 9 && e->buf[0] != '/'
		&& (e->files[e->selected]->color == C_DIR
		|| e->files[e->selected]->color == C_WHT))
	{
		NB_READ += 1;
		NB_MOVE += 1;
		ft_putchar('/');
		ft_realloc_insert_str(e, "/");
	}
	else if (e->buf[0] == 10 && (e->files[e->selected]->color == C_DIR
		|| e->files[e->selected]->color == C_WHT))
		ft_putstr_spec(e, "/");
	else if (NB_MOVE == NB_READ && (e->buf[0] == 10 || (e->c_match == 1
		&& (e->files[e->selected]->color != C_DIR
		&& e->files[e->selected]->color != C_WHT))))
	{
		NB_READ += 1;
		NB_MOVE += 1;
		ft_putchar(' ');
		ft_realloc_insert_str(e, " ");
	}	
}

int		valid_selection(t_env *e)
{
	int i;
	int ret;

	ret = 0;
	if (e->selected >= 0)
	{
		xputs(e->struct_tputs.cd);
		ret = 1;
		i = ft_strlen((e->files[e->selected]->name));
		ft_realloc_insert_str(e, (e->files[e->selected]->name));
		if (e->c_match == 1)
			ft_putstr((e->files[e->selected]->name));
		NB_READ += i;
		NB_MOVE += i;
		insert_after_comp(e);
		xputs(e->struct_tputs.cd);
		ft_putstr_spec(e, &e->line[NB_MOVE]);
	}
	else
		xputs(e->struct_tputs.cd);
	reset_autocomp(e);
	return (ret);
}
