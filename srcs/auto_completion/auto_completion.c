#include "shell.h"

static char	*get_path_from_arg(char *arg)
{
	char	*path;
	int		i;
	int		x;

	i = ft_strlen(arg);
	while (i > 0 && arg[i - 1] != '/')
		--i;
	if (!arg || !i || (i > 0 && arg[i - 1] == ' '))
		return ((path = getcwd(NULL, 0)));
	path = ft_strnew(i);
	ft_strncpy(path, arg, i);
	x = 0;
	while (path[x])
	{
		if (path[x] == '\\')
			ft_strncpy(&path[x], &path[x + 1], i - x);
		x++;
	}
	return (path);
}

static char	*isolate_arg_to_complete(char *arg)
{
	int		i;
	int		j;
	char	*ret;

	i = ft_strlen(arg);
	if (!arg || !i)
		return (arg);
	j = 0;
	while (i > 0 && arg[i - 1] != '/')
		--i;
	if (!(ret = ft_strnew(ft_strlen(arg) - i)))
		return (NULL);
	while (arg[i])
		ret[j++] = arg[i++];
	return (ret);
}

void		*ft_free_double_array(char **array)
{
	int i;

	i = 0;
	if (array)
	{
		while (array[i])
		{
			ft_strdel(&array[i]);
			i++;
		}
		free(array);
	}
	return (NULL);
}

int			ft_is_dir(char *target)
{
	struct stat	s;
	int			ret;

	ret = 0;
	if (stat(target, &s) != -1)
	{
		if (S_ISDIR(s.st_mode))
			ret = 1;
	}
	return (ret);
}

static void	complete_arg(t_env *e, char *arg)
{
	char	**content;
	char	*path;
	char	*tmp;

	tmp = NULL;
	if (arg)
	{
		if (arg[ft_strlen(arg) - 1 ] != '/' && ft_is_dir(arg))
		{
			arg = ft_strjoin(arg, "/");
			ft_putchar('/');
			ft_realloc_insert_str(e, "/");
			NB_READ += 1;
			NB_MOVE += 1;
			tmp = arg;
		}
	}
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
	while (content && e->selected >= -1)
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
		else if (tcaps_check_key(BUF, 27, 91, 67)
			|| tcaps_check_key(BUF, 9, 0, 0))
		{
			e->selected = e->selected + e->row < e->c_match ?
				e->selected + e->row : (e->selected + 1) % e->row;
			e->selected = e->selected >= e->c_match ? 0 : e->selected;
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
		}
		else
		{
			valid_selection(e);
			content = NULL;
			if (tcaps_is_printable(e->buf))
				tcaps_manage_printable_char(e);
			else if (tcaps_is_delete_key(e))
				e->line = ft_realloc_delete_char(e, NB_MOVE - 1);
			if (!tcaps_check_key(e->buf, 10, 0, 0))
				tcaps(e);
			ft_bzero(&e->buf, 3);
			return ;
		}
		print_auto_completion(e, NULL, NULL, NULL);
	}
	ft_bzero(&e->buf, 3);
}

char		*add_backquote(t_env *e, char *str, int i)
{
	int x;

	x = i;
	if (cur_inquote(e))
	{
		while (x > 0 && str[x] != ' ' && str[x] != '\'' && str[x] != '\"')
			x--;
		if (str[x] != '\'' || str[x] != '\"')
			x++;
	}
	else
	{
		while (x > 0 && (str[x] != ' ' || str[x - 1] == '\\'))
			x--;
	}
	if (str[x] == ' ')
		x++;
	return (ft_strsub(str, x, i - x + 1));
}

int			auto_completion(t_env *e)
{
	char	*arg_comp;

	if (!e->line)
		return (0);
	if (e->selected >= -1 && e->files)
	{
		e->selected = e->files[e->selected + 1] ? e->selected + 1 : 0;
		print_auto_completion(e, NULL, NULL, NULL);
	}
	else
	{
		arg_comp = add_backquote(e, e->line, TCAPS.nb_move - 1);
		complete_arg(e, arg_comp);
		ft_strdel(&arg_comp);
	}
	return (1);
}
