#include "shell.h"

/*
**		ADD NEW CMD TO THE END OF THE HISTORY TAB
*/

void	ft_check_history(t_env *e)
{
	int		i;
	int		accs;
	char	**tmp;

	accs = access(HIST_FILE, F_OK);
	ft_store_history(e->line);
	tmp = NULL;
	if (accs != -1)
	{
		i = ft_tablen(e->history);

		if (!ft_strcmp(e->history[i], e->line))
		{
			tmp = e->history;
			e->history = ft_tabcat(e->history, e->line);
			if (tmp)
				ft_free_tab(tmp);
		}
	}
	else if (e->history)
	{
		ft_free_tab(e->history);
		e->history = NULL;
		ft_read_history(e);
	}
	else
		ft_read_history(e);
}

/*
**		OPEN /tmp/.history AND STORE IT IN
**		e->history TAB
*/

int		ft_read_history(t_env *e)
{
	int			fd;
	int 		i;

	i = 0;
	if ((fd = open(HIST_FILE, O_RDONLY, OPENFLAGS)) == -1)
		return (ft_error(SH_NAME, "Cannot read", HIST_FILE));
	if ((e->history = malloc(sizeof(e->history) * 4096)) == NULL)
		//CLOSE FD BEFORE QUITTING
		return (ft_error(SH_NAME, "Malloc failed.", NULL));
	while (get_next_line(fd, &e->history[i]) > 0)
		++i;
	e->history[i] = NULL;
	if (close(fd) == -1)
		ft_printfd(2, "MANAGE ERROR");
	return (0);
}

/*
**		CREATE OR OPEN .history FILE
**		CONCAT WITH THE NEW CMD
*/

int		ft_store_history(char *cmd)
{
	int			fd;

	if ((fd = open(HIST_FILE, O_RDWR | O_CREAT | O_APPEND, OPENFLAGS)) == -1)
		return (-1);
	ft_putstr_fd(cmd, fd);
	ft_putchar_fd('\n', fd);
	if (close(fd) == -1)
		return (ft_error("close", "Could not close file", HIST_FILE));
	return (0);
}

/*
**		BUILTIN
**		PRINT CMD HISTORY
*/

int		ft_history(t_env *e)
{
	int		i;

	i = -1;
	if (e->history)
		while (e->history[++i])
			ft_printf("%d: %s\n", (i + 1), e->history[i]);
	return (0);
}
