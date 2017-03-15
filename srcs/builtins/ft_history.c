#include "shell.h"

/*
**		ADD NEW CMD TO THE END OF THE HISTORY TAB
*/

void	ft_store_history(t_env *e)
{
	int		i;
	char	**tmp;

	tmp = NULL;
	i = ft_tablen(e->history);
	tmp = e->history;
	e->history = ft_tabcat(e->history, e->line);
	if (tmp)
		ft_free_tab(tmp);
}

/*
**		OPEN /tmp/.history AND STORE IT IN
**		e->history TAB
*/

int		ft_read_history(t_env *e)
{
	int	history_fd;
	int 		i;

	i = 0;
	if ((history_fd = open(HIST_FILE, O_RDWR | O_CREAT, OPENFLAGS)) == -1)
		return (ft_error(SH_NAME, "Cannot read", HIST_FILE));
	if ((e->history = malloc(sizeof(e->history) * 4096)) == NULL)
		return (ft_error(SH_NAME, "Malloc failed.", NULL));
	while (get_next_line(history_fd, &e->history[i]) > 0)
		++i;
	e->history[i] = NULL;
	ft_close(history_fd);
	return (0);
}

/*
**		CREATE OR OPEN .history FILE
**		CONCAT WITH THE NEW CMD
*/

int		ft_write_history(t_env *e, int flag)
{
	int		history_fd;
	int		len_tab;
	int		i;
	char	*tmp;

	tmp = NULL;
	if ((history_fd = open(HIST_FILE, O_RDWR | O_CREAT | flag, OPENFLAGS)) == -1)
		return (ft_error(SH_NAME, "Cannot open/create history file", HIST_FILE));
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



int		isOption(char **cmd, char *option)
{
	int	i;

	i = 0;
	if (!cmd[1])
		return (0);
	while (cmd[++i])
		if (!ft_strcmp(cmd[i], option))
			return (1);
	return (0);
}

static void	history_delete(t_env *e, char **cmd)
{
	int		i;
	char	**tmp;

	if (isOnlyNumbers(cmd[2]))
		return ;
	i = ft_atoi(cmd[2]) - 1;
	if (i < 0 || !e->history[i])
		return ;
	tmp = e->history;
	e->history = delete_line_in_tab(e->history, i);
	ft_free_tab(tmp);
}

static void	print_history(t_env *e, char **cmd)
{
	int	i;
	int	arg;

	arg = -1;
	i = -1;
	if (cmd[1])
		arg = ft_atoi(cmd[1]);
	while (e->history[++i] && arg--)
		ft_printf("%d: %s\n", (i + 1), e->history[i]);
}

/*
**		BUILTIN
**		PRINT CMD HISTORY
*/

int		ft_history(t_env *e, char **cmd)
{
	if (isOption(cmd, "-c"))
	{
		ft_free_tab(e->history);
		e->history = NULL;
	}
	else if (isOption(cmd, "-d") && cmd[2])
		history_delete(e, cmd);
	else if (isOption(cmd, "-x"))
		ft_write_history(e, O_TRUNC);
	else if (isOption(cmd, "-a"))
		ft_write_history(e, O_APPEND);
	else if (e->history)
		print_history(e, cmd);
	return (0);
}
