#include "shell.h"

static int	start_by_nb(char *s)
{
	int	i;

	i = -1;
	while (s[++i] && is_number(s[i]))
		;
	if (!i)
		return (0);
	if (i && s[i] && !is_number(s[i]))
		return (1);
	return (0);
}

static int	finish_by_chev(char *s)
{
	int	len;

	len = (int)ft_strlen(s) - 1;
	if (len)
		return ((s[len] == '>' && s[len - 1] == '>'));
	return (0);
}

int			ft_check_input(int i, t_env *e)
{
	if (!ft_strcmp(e->magic[i].cmd, "<") ||
			!ft_strcmp("input", e->magic[i].type))
		return (1);
	return (0);
}

int			ft_check_output(int i, t_env *e)
{
	if (!ft_strcmp(e->magic[i].cmd, ">") ||
			!ft_strcmp(e->magic[i].cmd, ">>") ||
			!ft_strcmp(e->magic[i].cmd, "|") ||
			!ft_strcmp("output", e->magic[i].type))
		return (1);
	if (ft_strstr(e->magic[i].cmd, ">>")
		&& start_by_nb(e->magic[i].cmd)
		&& finish_by_chev(e->magic[i].cmd))
		return (1);
	return (0);
}

int			ft_check_heredoc(int i, t_env *e)
{
	if (!ft_strcmp(e->magic[i].cmd, "<<") &&
			ft_strcmp("heredoc", e->magic[i].type))
		return (1);
	return (0);
}
