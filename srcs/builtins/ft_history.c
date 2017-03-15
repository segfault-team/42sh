#include "shell.h"

int			ft_check_file_perm(char *file)
{
	int		ret;

	ret = 0;
	if (access(file, F_OK) != -1)
	{
		if (access(file, R_OK) == -1)
		{
			ft_error(SH_NAME, "Cannot access file for reading", file);
			ret = -1;
		}
		if (access(file, W_OK) == -1)
		{
			ft_error(SH_NAME, "Cannot access file for writing", file);
			ret = -1;
		}
	}
	return (ret);
}

/*
**		ADD NEW CMD TO THE END OF THE HISTORY TAB
*/

void	ft_check_history(t_env *e)
{
	int		i;
	int		accs;
	char	**tmp;

	accs = (HISTORY_FD > 0) ? 1 : -1;
	ft_store_history(e->line, HISTORY_FD);
	tmp = NULL;
	if (accs != -1)
	{
		i = ft_tablen(e->history);
		tmp = e->history;
		e->history = ft_tabcat(e->history, e->line);
		if (tmp)
			ft_free_tab(tmp);
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
	int 		i;

	i = 0;
	if ((HISTORY_FD = open(HIST_FILE, O_RDWR | O_CREAT, OPENFLAGS)) == -1)
		return (ft_error(SH_NAME, "Cannot read", HIST_FILE));
	if ((e->history = malloc(sizeof(e->history) * 4096)) == NULL)
		return (ft_error(SH_NAME, "Malloc failed.", NULL));
	while (get_next_line(HISTORY_FD, &e->history[i]) > 0)
		++i;
	e->history[i] = NULL;
	return (0);
}

/*
**		CREATE OR OPEN .history FILE
**		CONCAT WITH THE NEW CMD
*/

int		ft_store_history(char *cmd, int history_fd)
{
	ft_putstr_fd(cmd, history_fd);
	ft_putchar_fd('\n', history_fd);
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
