#include "shell.h"

static int      red_check_sign(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '&')
		return (1);
	return (0);
}

int				red_strstr(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (red_check_sign(str[i]))
			return (1);
	return (0);
}

int				struct_check_cmd(int i, t_env *e)
{
	if (i > 0 && e->magic[i - 1].cmd && !red_strstr(e->magic[i - 1].cmd) &&
		!red_strstr(e->magic[i].cmd))
		return (1);
	else if (i == 0 && !red_strstr(e->magic[i].cmd))
		return (1);
	return (0);
}

int				struct_check_red(int i, t_env *e)
{
	if (e->magic[i - 1].cmd && !red_strstr(e->magic[i - 1].cmd) &&
		!red_strstr(e->magic[i].cmd))
		return (1);
	return (0);
}

void			del_elem_magic(int i, t_env *e)
{
	ft_remove_tab(&e->cmd, i);
	free(e->magic[i - 1].type);
	e->magic[i - 1].type = ft_strdup("ignore");
}

void			struct_arg_red(int i, t_env *e)
{
	if ((i - 1 && !ft_strcmp(e->magic[i - 1].type, "input")) ||
		 (i - 1 && !ft_strcmp(e->magic[i - 1].type, "output")))
		del_elem_magic(i, e);
	if (ft_strstr(e->magic[i - 1].cmd, "<") ||
		ft_strstr(e->magic[i - 1].cmd, "<<") ||
		ft_strstr(e->magic[i - 1].cmd, "<&"))
		e->magic[i].type = ft_strdup("input");
	else
		e->magic[i].type = ft_strdup("output");
}
