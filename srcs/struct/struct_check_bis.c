#include "shell.h"

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
	return (0);
}

int			ft_check_heredoc(int i, t_env *e)
{
	if (!ft_strcmp(e->magic[i].cmd, "<<") &&
			ft_strcmp("heredoc", e->magic[i].type))
		return (1);
	return (0);
}
