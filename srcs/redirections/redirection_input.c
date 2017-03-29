#include "shell.h"

static int	input_error(t_env *e)
{
	if (!e->magic[RED_INDEX].cmd)
	{
		return (ft_error(SH_NAME, "syntax error near unexpected token",
					"'newline'"));
	}
	return (ft_error(SH_NAME, "syntax error near unexpected token",
				e->magic[RED_INDEX].cmd));
}

static int	is_last_cmd(t_env *e, int i)
{
	while (e->magic[i].cmd)
	{
		if (is_redir_pipe(e, i))
			return (0);
		++i;
	}
	return (1);
}

static void	do_for_last_cmd(t_env *e)
{
	FD.in = FD.fd[0];
	ft_close(FD.fd[1]);
}

int			redir_input(t_env *e)
{
	int		fd_file;
	int		red_index;
	int		ret;
	char	buf[4096];

	red_index = RED_INDEX - 1;
/*	while (e->magic[red_index].cmd && !is_input_file(e, red_index))
		if (is_redir_pipe(e, red_index++))
			return (0);*/
	ret = -1;
//	if (!e->magic[red_index].cmd || !is_input_file(e, red_index))
//		return (input_error(e));
	while (e->magic[++red_index].cmd && ft_strcmp(e->magic[red_index].cmd, "|"))
	{
		if (!ft_strcmp(e->magic[red_index].cmd, "<") && e->magic[red_index + 1].cmd
				&& !ft_strcmp(e->magic[red_index + 1].type, "input"))
		{
			if ((fd_file = open_file(e->magic[red_index + 1].cmd, O_RDONLY, 0)) == -1)
				return (-1);
			while ((ret = read(fd_file, &buf, 4095)))
			{
				buf[ret] = '\0';
				ft_putstr_fd(buf, FD.fd[1]);
			}
			ft_close(fd_file);
		}
	}
	if (is_input_redir(e, red_index))
		return (redir_input(e));
	if (is_last_cmd(e, red_index))
		do_for_last_cmd(e);
	return (1);
}
