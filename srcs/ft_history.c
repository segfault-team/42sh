#include "shell.h"
#include <fcntl.h>

/*
**	CREATE OR OPEN .history FILE
**	COMPLETE IT WITH THE NEW CMD
*/

int	store_history(char **cmd)
{
	int		i;
	int		j;
	int		fd;
	static char	*last_cmd = NULL;

	if (last_cmd && !ft_strcmp("history", last_cmd) && !ft_strcmp("history", cmd[0]))
		return (0);
	if (last_cmd)
		free(last_cmd);
	last_cmd = ft_strdup(cmd[0]);
	i = -1;
	if ((fd = open("/tmp/.history", O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR)) == -1)
		return (ft_printf("ERROR 0"));
	ft_putchar_fd('\n', fd);
	while (cmd[++i])
	{
		j = -1;
		while (cmd[i][++j])
			ft_putchar_fd(cmd[i][j], fd);
		ft_putchar_fd(' ', fd);
	}
	ft_putchar_fd('\n', fd);
	if (close(fd) == -1)
		ft_printf("ERROR 1");
	return (0);
}

/*
**	PRINT THE HISTORY OF CMD
*/

int	ft_history(void)
{
	int		i;
	int		fd;
	char	*rtr;

	i = 0;
	if ((fd = open("/tmp/.history", O_RDWR | O_CREAT, S_IRUSR, S_IWUSR)) == -1)
		return (ft_printf("GERER ERROR"));
	while (get_next_line(fd, &rtr) > 0)
		// GERER REDIRECTION
		if (rtr)
			ft_printfd(1, " %d\t%s\n", ++i, rtr);
	if (close(fd) == -1)
		ft_printf("GERER ERREUR");
	return (0);
}
