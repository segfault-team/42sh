#include "shell.h"

static void	reset_autocomp(t_env *e)
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

static void	insert_after_comp(t_env *e)
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

int			valid_selection(t_env *e)
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
