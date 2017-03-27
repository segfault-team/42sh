#include "shell.h"

int		history_delete(t_env *e, char **cmd, int curr)
{
	int		i;
	int		j;
	char	**tmp;

	i = (e->cmd[curr][2]) ? 0 : -1;
	j = 1;
	if (!i)
	{
		while (e->cmd[curr][++j])
		{
			if (!is_number(e->cmd[curr][j]))
				return (history_delete_error(SH_NAME, cmd));
			i = i * 10 + e->cmd[curr][j] - '0';
		}
		--i;
	}
	else if (!e->cmd[curr + 1])
		return (history_delete_error(SH_NAME, cmd));
	else
	{
		if (!is_only_numbers(cmd[curr + 1]) && i == -1)
			return (history_delete_error(SH_NAME, cmd));
		i = ft_atoi(cmd[curr + 1]) - 1;
	}
	if (i < 0 || !e->history[i])
		return (history_delete_error(SH_NAME, cmd));
	tmp = e->history;
	e->history = delete_line_in_tab(e->history, i);
	ft_free_tab(tmp);
	return (1);
}

int		print_history(t_env *e, char **cmd)
{
	size_t	i;
	int		arg;
	int		len_tab;

	arg = 0;
	i = -1;
	len_tab = ft_tablen(e->history);
	if (cmd[1])
	{
		arg = (size_t)atoi_bis(cmd[1]);
		if (arg == -1)
			return (history_error_with_id(cmd, SH_NAME, 2));
		i = ft_tablen(e->history) - arg - 1;
	}
	if (i + 1 > (size_t)len_tab)
		i = -1;
	while (e->history[++i])
		ft_printf("%d: %s\n", (i + 1), e->history[i]);
	return (0);
}

void	clear_history_list(t_env *e)
{
	if (e->history)
	{
		ft_free_tab(e->history);
		e->history = NULL;
	}
	e->trunc_in_history = 1;
}

int		append_history_file_in_list(t_env *e)
{
	int		history_fd;
	int		len;
	int		nb_lines;
	char	**new;
	int		i;

	if ((history_fd = open(HIST_FILE, O_RDWR | O_CREAT, OFLAGS)) == -1)
		return (ft_error(SH_NAME, "Cannot read", HIST_FILE));
	len = ft_tablen(e->history) + 4096;
	nb_lines = 0;
	i = -1;
	if ((new = malloc(sizeof(e->history) * len)) == NULL)
		return (ft_error(SH_NAME, "Malloc failed.", NULL));
	while (e->history[++i])
		new[i] = e->history[i];
	new[i] = NULL;
	while (++nb_lines < 4096 && get_next_line(history_fd, &new[i]) > 0)
		++i;
	new[++i] = NULL;
	ft_close(history_fd);
	ft_free_tab(e->history);
	e->history = new;
	return (1);
}

void	print_history_help(void)
{
	ft_printfd(2, "history: usage: history -[acdhrw]\n");
	ft_printfd(2, "-a: \t\tprint list in file\n");
	ft_printfd(2, "-c: \t\tclear the list\n");
	ft_printfd(2, "-d INDEX: \tdelete history cmd at INDEX\n");
	ft_printfd(2, "-h: \t\tshow this message\n");
	ft_printfd(2, "-r: \t\tappend history file in list\n");
	ft_printfd(2, "-w: \t\twrite list in history file\n");
}
