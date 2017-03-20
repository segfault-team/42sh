#include "shell.h"

void history_delete(t_env *e, char **cmd)
{
	int     i;
	char    **tmp;

	if (!isOnlyNumbers(cmd[2]))
		return ;
	i = ft_atoi(cmd[2]) - 1;
	if (i < 0 || !e->history[i])
		return ;
	tmp = e->history;
	e->history = delete_line_in_tab(e->history, i);
	ft_free_tab(tmp);
}

void print_history(t_env *e, char **cmd)
{
	int     i;
	int     arg;

	arg = 0;
	i = -1;
	if (cmd[1])
	{
		arg = ft_atoi(cmd[1]);
		i = ft_tablen(e->history) - arg - 1;
	}
	while (e->history[++i])
		ft_printf("%d: %s\n", (i + 1), e->history[i]);
}

void clear_history_list(t_env *e)
{
	if (e->history)
	{
		ft_free_tab(e->history);
		e->history = NULL;
	}
	e->trunc_in_history = 1;
}

int  append_history_file_in_list(t_env *e)
{
	int     history_fd;
	int     len;
	int     nb_lines;
	char    **new;
	int     i;

	if ((history_fd = open(HIST_FILE, O_RDWR | O_CREAT, OFLAGS)) == -1)
		return (ft_error(SH_NAME, "Cannot read", HIST_FILE));
	len = ft_tablen(e->history) + 4096;
	nb_lines = 0;
	i = -1;
	if ((new = malloc(sizeof(e->history) * len)) == NULL)
		return (ft_error(SH_NAME, "Malloc failed.", NULL));
	while (e->history[++i])
		new[i] = e->history[i];
	while (++nb_lines < 4096 && get_next_line(history_fd, &new[i]) > 0)
		++i;
	new[i] = NULL;
	ft_close(history_fd);
	ft_free_tab(e->history);
	e->history = new;
	return (1);
}

void        print_history_help(void)
{
	ft_printf("history: usage: history -[acdhrw]\n");
	ft_printf("-a: \t\tprint list in file\n");
	ft_printf("-c: \t\tclear the list\n");
	ft_printf("-d INDEX: \tdelete history cmd at INDEX\n");
	ft_printf("-h: \t\tshow this message\n");
	ft_printf("-r: \t\tappend history file in list\n");
	ft_printf("-w: \t\twrite list in history file\n");
}
