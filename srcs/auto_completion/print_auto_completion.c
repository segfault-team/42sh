#include "shell.h"

int			ft_putstr_color(char *prefix, char *str, char *color)
{
	int		i;

	i = 0;
	ft_putstr_fd(color, 2);
	ft_putstr_fd(prefix, 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(C_RESET, 2);
	return (i);
}

void		ft_print_ext(t_env *e, char *color, char *spaces)
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

void		ft_put_file(t_env *e, int i, char *spaces)
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

int			ft_sslen(char **s)
{
	int i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

static char	*ft_pick_color(char *perm)
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

static char	ft_file_type(int mode)
{
	char	c;

	if (S_ISREG(mode))
		c = '-';
	else if (S_ISDIR(mode))
		c = 'd';
	else if (S_ISBLK(mode))
		c = 'b';
	else if (S_ISCHR(mode))
		c = 'c';
	else if (S_ISFIFO(mode))
		c = 'p';
	else if (S_ISLNK(mode))
		c = 'l';
	else if (S_ISSOCK(mode))
		c = 's';
	else
		c = '?';
	return (c);
}

static char	*ft_perms(int mode)
{
	char	*rwx[8];
	char	*bits;

	bits = (char *)malloc(12 * sizeof(char *));
	rwx[0] = "---";
	rwx[1] = "--x";
	rwx[2] = "-w-";
	rwx[3] = "-wx";
	rwx[4] = "r--";
	rwx[5] = "r-x";
	rwx[6] = "rw-";
	rwx[7] = "rwx";
	bits[0] = ft_file_type(mode);
	ft_strcpy(&bits[1], rwx[(mode >> 6) & 7]);
	ft_strcpy(&bits[4], rwx[(mode >> 3) & 7]);
	ft_strcpy(&bits[7], rwx[(mode & 7)]);
	if (mode & S_ISUID)
		bits[3] = (mode & S_IXUSR) ? 's' : 'S';
	if (mode & S_ISGID)
		bits[6] = (mode & S_IXGRP) ? 's' : 'S';
	if (mode & S_ISVTX)
		bits[9] = (mode & S_IXUSR) ? 't' : 'T';
	bits[10] = ' ';
	bits[11] = '\0';
	return (bits);
}

char		*file_with_path(t_env *e, char *str)
{
	int		x;
	int		i;
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(e->prefix, str);
	tmp2 = ft_strjoin(e->path, tmp);
	ft_strdel(&tmp);
	x = 0;
	i = ft_strlen(tmp2);
	while (tmp2 && tmp2[x])
	{
		if (tmp2[x] == '\\')
			ft_strncpy(&tmp2[x], &tmp2[x + 1], i - x);
		x++;
	}
	return (tmp2);
}

void		ft_fill_files(char **argv, t_env *e)
{
	int				i;
	struct stat		s;
	char			*tmp;
	char			*tmp2;

	i = 0;
	while (argv[i])
	{
		e->files[i] = (t_file *)malloc(sizeof(t_file));
		e->files[i]->name = ft_strdup(argv[i]);
		if (e->total_len < ft_strlen(argv[i]))
		{
			e->total_len = ft_strlen(argv[i]);
			e->total_len = e->total_len < e->tcaps.ws.ws_col ?
				e->total_len : e->tcaps.ws.ws_col - 3;
		}
		tmp = NULL;
		tmp2 = file_with_path(e, argv[i]);
		if (lstat(tmp2, &s) == -1)
			tmp = ft_strdup(C_RESET);
		if (!tmp)
			tmp = ft_perms(s.st_mode);
		e->files[i]->color = ft_pick_color(tmp);
		ft_strdel(&tmp);
		ft_strdel(&tmp2);
		i++;
	}
	e->c_match = i;
	e->files[i] = NULL;
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

void	actual_print(t_env *e)
{
	int		i;
	char	*tmp;
	int		moar;

	i = e->start;
	e->printed = -1;
	moar = 0;
	e->row = calc_rows(e);
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
	if (e->selected >= 0)
		ft_putstr(e->files[e->selected]->name);
	xputs(e->struct_tputs.ce);
	ft_putstr_spec(e, &e->line[NB_MOVE]);
	if (e->printed < 0 && e->selected >= 0)
	{
		e->start = e->start + 1 < e->row ? e->start + 1 : 0;
		actual_print(e);
	}
}

void	print_auto_completion(t_env *e, char *arg, char *path, char **content)
{
	if (path)
	{
		e->path = ft_strjoin(path, "/");
		ft_strdel(&path);
		e->prefix = arg;
		e->files = (t_file **)malloc((ft_sslen(content) + 1) * sizeof(t_file*));
		e->files[ft_sslen(content)] = NULL;
		ft_fill_files(content, e);
		ft_free_tab(content);
	}
	if (e->c_match == 1)
	{
		e->selected = 0;
		valid_selection(e);
	}
	else if (e->selected >= -1)
		actual_print(e);
}

int	valid_selection(t_env *e)
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
		if (e->buf[0] != 10 && e->buf[0] != 9 && e->buf[0] != '/'
			&& (e->files[e->selected]->color == C_DIR
			|| e->files[e->selected]->color == C_WHT))
		{
			NB_READ += 1;
			NB_MOVE += 1;
			ft_putchar('/');
			ft_realloc_insert_str(e, "/");
		}
		else if (e->buf[0] == 10 && e->files[e->selected]->color == C_DIR)
			ft_putstr_spec(e, "/");
		else if (NB_MOVE == NB_READ && (e->buf[0] == 10 || (e->c_match == 1
			&& (e->files[e->selected]->color == C_DIR
			|| e->files[e->selected]->color == C_WHT))))
		{
			NB_READ += 1;
			NB_MOVE += 1;
			ft_putchar(' ');
			ft_realloc_insert_str(e, " ");
		}
		xputs(e->struct_tputs.cd);
		ft_putstr_spec(e, &e->line[NB_MOVE]);
	}
	else
		xputs(e->struct_tputs.cd);
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
	return (ret);
}
