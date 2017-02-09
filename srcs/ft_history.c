#include "shell.h"

int			ft_check_file_perm(char *file)
{
	int		ret;

	ret = 0;
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
	return (ret);
}

/*
**	CREATE OR OPEN .history FILE
**	COMPLETE IT WITH THE NEW CMD
*/

int		ft_store_history(char *cmd)
{
	int		i;
	int		fd;
	static char	*last_cmd = NULL;

	if (last_cmd && cmd && !ft_strcmp(cmd, last_cmd))
		return (0);
	if (last_cmd)
		free(last_cmd);
	last_cmd = ft_strdup(cmd);
	if ((fd = open(HISTORY_FILE, O_RDWR | O_CREAT | O_APPEND, OPENFLAGS)) == -1)
		// We have a error because we try to open it with read AND WRITE rights
		// Error is managed like this because it's useless to report
		// error message more than once
		// So trying to open file once on startup and in case
		// report error is enough.
		return (-1);
	i = -1;
	ft_putstr_fd(cmd, fd);
/*	while (cmd[++i])
	{
		ft_putstr_fd(cmd[i], fd);
		if (cmd[i + 1])
			ft_putchar_fd(' ', fd);
	}
*/	ft_putchar_fd('\n', fd);
	if (close(fd) == -1)
		return (ft_error("close", "Could not close file", HISTORY_FILE));
	return (0);
}

/*
**	HISTORY BUILTIN
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
