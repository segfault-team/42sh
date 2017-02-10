#include "shell.h"

/*
**	CREATE OR OPEN .history FILE
**	COMPLETE IT WITH THE NEW CMD
*/

int		ft_store_history(char *cmd)
{
	int		fd;
	static char	*last_cmd = NULL;

	if (last_cmd && !ft_strcmp(cmd, last_cmd))
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
	ft_putstr_fd(cmd, fd);
	ft_putchar_fd('\n', fd);
	if (close(fd) == -1)
		return (ft_error("close", "Could not close file", "/tmp/.history"));
	return (0);
}

/*
**	PRINT THE HISTORY OF CMD
*/

int		ft_history(t_env *e)
{
	int		i;
/*	int		fd;
	char	*rtr;*/

	i = -1;
	if (e->history)
		while (e->history[++i])
			ft_printf("%d: %s\n", (i + 1), e->history[i]);
/*	if ((fd = open("/tmp/.history", O_RDWR | O_CREAT, S_IRUSR, S_IWUSR)) == -1)
		return (ft_printf("GERER ERROR"));
	while (get_next_line(fd, &rtr) > 0)
		// GERER REDIRECTION
		if (rtr)
			ft_printfd(1, " %d\t%s\n", ++i, rtr);
	if (close(fd) == -1)
		ft_printf("GERER ERREUR");*/
	return (0);
}
