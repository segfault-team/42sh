#include "shell.h"

static void	do_for_last_cmd(t_env *e)
{

//	if (is_next_redir(e, RED_INDEX) == PIPE || is_next_redir(e, RED_INDEX) == OUTPUT)
//		ft_close(FD.fd[1]);
}

int			is_last_cmd(t_env *e, int i)
{
	if (!e->magic[i].cmd)
		return (1);
	if (is_redir_pipe(e, i))
		++i;
	while (e->magic[i].cmd && !is_operator(e, i))
	{
		if (is_redir_pipe(e, i))
			return (0);
		++i;
	}
	return (1);
}

static int	redir_input_do(t_env *e, int newfd[2])
{
	int		fd_file;
	int		ret;
	char	buf[4096];

	fd_file = 0;
	ret = -1;
	if ((fd_file = open_file(e->magic[RED_INDEX + 1].cmd, O_RDONLY, 0)) == -1)
		return (-1);
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
	return (1);
}
