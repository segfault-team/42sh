#include "shell.h"

static void	do_for_last_cmd(t_env *e)
{
	FD.in = FD.fd[0];
	if (!is_last_cmd(e, RED_INDEX))
		ft_close(FD.fd[1]);
}

int			is_last_cmd(t_env *e, int i)
{
	if (is_redir_pipe(e, i))
		++i;
	while (e->magic[i].cmd)
	{
		if (is_redir_pipe(e, i))
			return (0);
		++i;
	}
	return (1);
}

static int	redir_input_do(t_env *e, int red_index)
{
	int		fd_file;
	int		ret;
	char	buf[4096];

	fd_file = 0;
	ret = -1;
	if ((fd_file = open_file(e->magic[red_index + 1].cmd, O_RDONLY, 0)) == -1)
		return (-1);
	while ((ret = read(fd_file, &buf, 4095)))
	{
		buf[ret] = '\0';
		ft_putstr_fd(buf, FD.fd[1]);
	}
	ft_close(fd_file);
	return (0);
}

int			redir_input(t_env *e)
{
	int		fd_file;
	int		red_index;
	int		ret;
	char	buf[4096];

	red_index = RED_INDEX - 1;
	ret = -1;
	while (e->magic[++red_index].cmd && ft_strcmp(e->magic[red_index].cmd, "|"))
	{
		if (!ft_strcmp(e->magic[red_index].cmd, "<")
				&& e->magic[red_index + 1].cmd
				&& !ft_strcmp(e->magic[red_index + 1].type, "input"))
			if (redir_input_do(e, red_index) < 0)
				return (-1);
	}
	if (is_input_redir(e, red_index))
		return (redir_input(e));
	if (is_last_cmd(e, red_index))
		do_for_last_cmd(e);
	return (1);
}
