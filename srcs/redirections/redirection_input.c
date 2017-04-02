#include "shell.h"

static int	redir_input_do(t_env *e, int newfd[2])
{
	int		fd_file;
	int		ret;
	char	buf[4096];

	fd_file = 0;
	ret = -1;
	if ((fd_file = open_file(e->magic[RED_INDEX + 1].cmd, O_RDONLY, 0)) == -1)
	{
		FD.in = newfd[0];
		ft_close(newfd[1]);
		return (-1);
	}
	while ((ret = read(fd_file, &buf, 4095)))
	{
		buf[ret] = '\0';
		ft_putstr_fd(buf, newfd[1]);
	}
	ft_close(fd_file);
	ft_close(newfd[1]);
	return (0);
}

int			redir_input(t_env *e)
{
	int		fd_file;
	int		red_index;
	int		ret;
	char	buf[4096];
	int		newfd[2];

	pipe(newfd);
	ret = -1;
	if (e->check_input)
	{
		while ((ret = read(FD.in, &buf, 4095)) > 0)
		{
			buf[ret] = '\0';
			ft_putstr_fd(buf, newfd[1]);
		}
		ft_close(FD.in);
	}
	if (redir_input_do(e, newfd) < 0)
		return (-1);
	FD.in = newfd[0];
	dprintf(2, "IN: %d\n", FD.in);
	return (1);
}
