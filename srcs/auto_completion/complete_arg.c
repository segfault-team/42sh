#include "shell.h"

static int	autoc_tcaps_one(t_env *e)
{
	if (tcaps_check_key(BUF, 27, 91, 67)
			|| tcaps_check_key(BUF, 9, 0, 0))
	{
		e->selected = e->selected + e->row < e->c_match ?
			e->selected + e->row : (e->selected + 1) % e->row;
		e->selected = e->selected >= e->c_match ? 0 : e->selected;
		return (1);
	}
	else if (tcaps_check_key(BUF, 27, 91, 68)
			|| tcaps_check_key(BUF, 27, 91, 90))
	{
		if (!e->selected)
			e->selected = e->row * (e->c_match / e->row) + (e->row - 1);
		else
			e->selected = e->selected - e->row >= 0 ?
				e->selected - e->row :
				(e->selected - 1) + (e->row) * (e->c_match / e->row);
		while (e->selected > e->c_match - 1)
			e->selected -= e->row;
		return (1);
	}
	return (0);
}

static int	autoc_tcaps_end(t_env *e, char ***content)
{
	valid_selection(e);
	*content = NULL;
	if (tcaps_is_printable(e->buf))
		tcaps_manage_printable_char(e);
	else if (tcaps_is_delete_key(e))
		e->line = ft_realloc_delete_char(e, NB_MOVE - 1);
	if (!tcaps_check_key(e->buf, 10, 0, 0))
		tcaps(e);
	ft_bzero(&e->buf, 3);
	return (0);
}

static int	complete_arg_tcaps(t_env *e, char ***content)
{
	while (*content && e->selected >= -1)
	{
		ft_bzero(&e->buf, 3);
		read(0, e->buf, 3);
		if (e->check_ctrl_c)
			e->check_ctrl_c = 0;
		if (BUF[0] == CTRL_D)
			e->selected = -1;
		else if (e->selected == -1 && (BUF[0] == 9 || BUF[1] == 91))
			e->selected = 0;
		else if (tcaps_check_key(BUF, 27, 91, 66))
			e->selected = e->selected + 1 < e->c_match ? e->selected + 1 : 0;
		else if (tcaps_check_key(BUF, 27, 91, 65))
			e->selected = e->selected ? e->selected - 1 : e->c_match - 1;
		else if (autoc_tcaps_one(e))
			;
		else
			return (autoc_tcaps_end(e, content));
		print_auto_completion(e, NULL, NULL, NULL);
	}
	return (1);
}

static void	autoc_check_arg(t_env *e, char *arg, char **tmp)
{
	if (arg)
	{
		if (arg[ft_strlen(arg) - 1] != '/' && ft_is_dir(arg))
		{
			arg = ft_strjoin(arg, "/");
			ft_putchar('/');
			ft_realloc_insert_str(e, "/");
			NB_READ += 1;
			NB_MOVE += 1;
			*tmp = arg;
		}
	}
}

void		complete_arg(t_env *e, char *arg)
{
	char	**content;
	char	*path;
	char	*tmp;

	tmp = NULL;
	autoc_check_arg(e, arg, &tmp);
	path = get_path_from_arg(arg);
	arg = isolate_arg_to_complete(arg);
	content = get_valid_content_from_path(e, path, arg);
	ft_strdel(&tmp);
	if (content)
	{
		e->selected = -1;
		print_auto_completion(e, arg, path, content);
	}
	else
	{
		ft_strdel(&path);
		ft_strdel(&arg);
	}
	if (!complete_arg_tcaps(e, &content))
		return ;
	ft_bzero(&e->buf, 3);
}
