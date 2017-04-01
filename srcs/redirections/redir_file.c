#include "shell.h"

static void		redir_output_do(t_env *e, int fd, int i, char *out)
{
	int		red;

	red = ft_strcmp(e->magic[i].cmd, ">>");
	if ((fd = open(e->magic[i + 1].cmd,
		(!red ? TWO_RED_FLAGS : ONE_RED_FLAGS), OFLAGS)) > -1)
	{
		ft_printfd(fd, "%s", out ? out : "");
		if (out && out[(int)ft_strlen(out) - 1] != '\n')
			ft_printfd(fd, "\n");
		ft_close(fd);
	}
	else
		ft_error(SH_NAME, "failed opening file",\
			e->magic[i].cmd ? e->magic[i].cmd : NULL);
}

static int		redir_file_output(t_env *e, char *ret_output)
{
	int		fd_output;
	int		i;

	i = RED_INDEX - 1;
	fd_output = 0;
	while (e->magic[++i].cmd && ft_strcmp(e->magic[i].cmd, "|"))
		if ((!ft_strcmp(e->magic[i].cmd, ">")
				|| !ft_strcmp(e->magic[i].cmd, ">>"))
				&& e->magic[i + 1].cmd &&
				!ft_strcmp(e->magic[i + 1].type, "output"))
			redir_output_do(e, fd_output, i, ret_output);
	strfree(&ret_output);
	return (1);
}

int				redir_fill_output(t_env *e)
{
	char	*ret_output;
	char	tmp[4096];
	char	*tmp_join;
	int		len;

	tmp_join = NULL;
	ret_output = NULL;
	ft_bzero(tmp, 4095);
	while ((len = read(FD.in, &tmp, 4095)) > 0)
	{
		tmp[len] = '\0';
		if (!ret_output)
			ret_output = ft_strdup(tmp);
		else if ((tmp_join = ft_strjoin(ret_output, tmp)))
		{
			strfree(&ret_output);
			ret_output = tmp_join;
		}
	}
	return (redir_file_output(e, ret_output));
}
