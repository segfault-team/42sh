#include "shell.h"

/*
**		ADD NEW CMD TO THE END OF THE HISTORY TAB
*/

void		ft_store_history(t_env *e)
{
	char		**tmp;
	int			is_not_history_cmd;

	tmp = NULL;
	tmp = e->history;
	is_not_history_cmd = ft_strcmp(e->line, "history");
	if (is_not_history_cmd ||
		(e->last_cmd && ft_strcmp(e->last_cmd, "history")) || !e->last_cmd)
	{
		e->history = ft_tabcat(e->history, e->line);
		if (tmp)
			ft_free_tab(tmp);
	}
	strfree(&e->last_cmd);
	e->last_cmd = ft_strdup(e->line);
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
		return (ft_error(SH_NAME, "Cannot read", HIST_FILE));
	nb_lines = 0;
	if ((e->history = malloc(sizeof(e->history) * 4096)) == NULL)
		return (ft_error(SH_NAME, "Malloc failed.", NULL));
	while (++nb_lines < 4096 && get_next_line(history_fd, &e->history[i]) > 0)
		++i;
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
		return (ft_error(SH_NAME, "Cannot open history file", HIST_FILE));
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
	int		ret;

	ret = -1;
	if (i == 1 && is_valid_arg(cmd, SH_NAME) < 0)
		return (-1);
	if (!e->history)
		return (-1);
	if (is_option(i, cmd, "-d"))
		ret = history_delete(e, cmd, i);
	else if (is_option(i, cmd, "-w"))
		ret = ft_write_history(e, O_TRUNC);
	else if (is_option(i, cmd, "-a"))
		ret = ft_write_history(e, O_APPEND);
	else if (is_option(i, cmd, "-c"))
		ret = clear_history_list(e);
	else if (is_option(i, cmd, "-r"))
		ret = append_history_file_in_list(e);
	else if (is_option(i, cmd, "-h"))
		ret = print_history_help();
	else if (is_option(i, cmd, "-p"))
		ret = print_history_help();
	else if (e->history)
		ret = print_history(e, cmd);
	if (ret != -1 && cmd[i + 1] && !is_redirection(e, i + 1))
		return (ft_history(e, cmd, i + 1));
	return (ret);
}
