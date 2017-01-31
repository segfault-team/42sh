#include "shell.h"

/*
**	CREATE OR OPEN .history FILE
**	COMPLETE IT WITH THE NEW CMD
*/

int		ft_store_history(char **cmd)
{
	int		i;
	int		fd;
	static char	*last_cmd = NULL;

	if (last_cmd && !ft_strcmp(cmd[0], last_cmd))
		return (0);
	if (last_cmd)
		free(last_cmd);
	last_cmd = ft_strdup(cmd[0]);
	if ((fd = open("/tmp/.history", O_RDWR | O_CREAT | O_APPEND, OPENFLAGS)) == -1)
		return (ft_error("open", "Could not open file", "/tmp/.history"));
	i = -1;
	while (cmd[++i])
	{
		ft_putstr_fd(cmd[i], fd);
		if (cmd[i + 1])
			ft_putchar_fd(' ', fd);
	}
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
