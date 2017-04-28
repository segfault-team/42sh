#include "shell.h"

/*
**		ADD NEW CMD TO THE END OF THE HISTORY TAB
*/

void		ft_store_history(t_env *e)
{
	char		**tmp;
	char		*line_cpy;
	int			x;

	x = -1;
	tmp = e->history;
	line_cpy = ft_strdup(e->line);
	while (line_cpy && line_cpy[++x])
		if (x > 0 && line_cpy[x] && line_cpy[x] == '\n')
		{
			line_cpy = ft_delete_char(line_cpy, x);
			--x;
		}
	e->history = ft_tabcat(e->history, line_cpy);
	if (tmp)
		ft_free_tab(tmp);
	strfree(&line_cpy);
}

/*
**		OPEN ~/.sh_history AND STORE IT IN
**		e->history TAB
*/

int			ft_read_history(t_env *e)
{
	int		history_fd;
	int		i;
	int		nb_lines;

	i = 0;
	if ((history_fd = open(HIST_FILE, O_RDWR | O_CREAT, OFLAGS)) == -1)
		return (ft_error("Cannot read", HIST_FILE, NULL));
	nb_lines = 0;
	if ((e->history = malloc(sizeof(e->history) * 4096)) == NULL)
		return (ft_error(NULL, "Malloc failed.", NULL));
	while (++nb_lines < 4096 && get_next_line(history_fd, &e->history[i]) > 0)
	{
		if (!(e->history[i] = convert_tabs(e->history[i])))
			break ;
		++i;
	}
	e->history[i] = NULL;
	return (1);
}

/*
**		CREATE OR OPEN .sh_history FILE
**		CONCAT WITH THE NEW CMD
*/

int			ft_write_history(t_env *e, int flag)
{
	int		history_fd;
	int		len_tab;
	int		i;
	char	*tmp;

	tmp = NULL;
	flag = (e->trunc_in_history) ? O_TRUNC : flag;
	if ((history_fd = open(HIST_FILE, O_RDWR | O_CREAT | flag, OFLAGS)) == -1)
		return (ft_error("Cannot open history file", HIST_FILE, NULL));
	len_tab = ft_tablen(e->history);
	i = -1;
	while (++i < len_tab)
	{
		tmp = ft_strjoin(e->history[i], "\n");
		write(history_fd, tmp, (int)ft_strlen(tmp));
		strfree(&tmp);
	}
	ft_close(history_fd);
	return (1);
}

/*
**	CHECK IF OPTION IS PRESENT IN CMD
*/

int			is_option(int i, char **cmd, char *option)
{
	if (!cmd[i])
		return (0);
	if (ft_strstr(cmd[i], option))
		return (1);
	return (0);
}

/*
**		BUILTIN
**		PRINT CMD HISTORY
*/

int			ft_history(t_env *e, char **cmd, int i)
{
	int			ret;
	t_opt_hist	opt;

	ret = -1;
	init_opt_hist(&opt);
	if (i == 1 && get_hist_options(i, cmd, &opt) == -1)
		return (-1);
	if (opt.d)
		ret = history_delete(e, cmd, opt.i_opt_d);
	else if (opt.w)
		ret = ft_write_history(e, O_TRUNC);
	else if (opt.a)
		ret = ft_write_history(e, O_APPEND);
	else if (opt.c)
		ret = clear_history_list(e);
	else if (opt.r)
		ret = append_history_file_in_list(e);
	else if (opt.h)
		ret = print_history_help();
	else if (e->history)
		ret = print_history(e, cmd);
	return (ret);
}
