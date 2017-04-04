#include "shell.h"

int		is_redirection(t_env *e, int i)
{
	if (i >= e->len_mag)
		return (0);
	if (e->magic[i].type && !ft_strcmp(e->magic[i].type, "red"))
		return (1);
	return (0);
}

int		is_output_redir(t_env *e, int i)
{
	if (i >= e->len_mag)
		return (0);
	if (!ft_strcmp(e->magic[i].cmd, ">") ||
		!ft_strcmp(e->magic[i].cmd, ">>"))
		return (1);
	return (0);
}

int		is_input_redir(t_env *e, int i)
{
	if (i >= e->len_mag)
		return (0);
	if (!ft_strcmp(e->magic[i].cmd, "<"))
		return (1);
	return (0);
}

int		is_heredoc(t_env *e, int i)
{
	if (i >= e->len_mag)
		return (0);
	if (!ft_strcmp(e->magic[i].cmd, "<<"))
		return (1);
	return (0);
}

int		is_aggregator(t_env *e, int i)
{
	if (i >= e->len_mag)
		return (0);
	if (ft_strstr(e->magic[i].cmd, "<&") ||
		ft_strstr(e->magic[i].cmd, ">&"))
		return (1);
	return (0);
}
