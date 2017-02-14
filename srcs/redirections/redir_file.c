#include "shell.h"

static int		struct_find_out(t_env *e)
{
	int mem_red_index;

	mem_red_index = RED_INDEX;
	while (e->magic[RED_INDEX].cmd && ft_strcmp(e->magic[RED_INDEX].type, "red"))
		++RED_INDEX;
	if (!(e->magic[RED_INDEX].cmd))
	{
		RED_INDEX = mem_red_index;
		return (0);
	}
	return (1);
}

static int		nombrederedirectionsdanslacommande(t_env *e)
{
	int		nb_red;
	int		i;

	nb_red = 0;
	i = RED_INDEX;
	while (e->magic[i].type)
	{
		if (!ft_strcmp(e->magic[i].type, "red"))
			++nb_red;
		++i;
	}
	return (nb_red);
}

static int		redir_file_output(t_env *e, char *ret_output)
{
	int		fd_output;
	int		nb_red;
	int		red_type;

	red_type = 0;
	nb_red = nombrederedirectionsdanslacommande(e);
	fd_output = 0;
	while (nb_red-- && struct_find_out(e))
	{
		red_type = ft_strcmp(e->magic[RED_INDEX].cmd, ">>"); 
		if ((fd_output = open(e->magic[++RED_INDEX].cmd, (!red_type ? TWO_RED_FLAGS : ONE_RED_FLAGS),\
			OPENFLAGS)) > -1)
		{
			// NE PAS ENLEVER
			ft_printfd(fd_output, "%s", ret_output);
			ft_close(fd_output);
		}
		else
			ft_error(SH_NAME, "failed opening file",\
					e->magic[RED_INDEX].cmd ? e->magic[RED_INDEX].cmd : NULL);
	}
	free(ret_output);
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
	while ((len = read(FD.in, &tmp, 4095)) > 0)
	{
		tmp[len] = '\0';
		if (!ret_output)
			ret_output = ft_strdup(tmp);
		else if ((tmp_join = ft_strjoin(ret_output, tmp)))
		{
				free(ret_output);
				ret_output = tmp_join;
		}
	}
	return (redir_file_output(e, ret_output));
}
