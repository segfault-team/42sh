#include "shell.h"

int	isRedirection(t_env *e, int i)
{
	if (!ft_strcmp(e->magic[i].type, "red"))
		return (1);
	return (0);
}

int isOutputRedir(t_env *e, int i)
{
	if (!ft_strcmp(e->magic[i].cmd, ">") || !ft_strcmp(e->magic[i].cmd, ">>"))
		return (1);
	return (0);
}

int isInputRedir(t_env *e, int i)
{
	if (!ft_strcmp(e->magic[i].cmd, "<") || !ft_strcmp(e->magic[i].cmd, "<<"))
		return (1);
	return (0);
}

int isAggregator(t_env *e, int i)
{
	if (ft_strstr(e->magic[i].cmd, "<&") || ft_strstr(e->magic[i].cmd, ">&"))
		return (1);
	return (0);
}

int	isRedirPipe(t_env *e, int i)
{
	if (!ft_strcmp(e->magic[i].cmd, "|"))
		return (1);
	return (0);
}

int	isNextRedir(t_env *e, int i)
{
	++i;
	while (e->magic[i].cmd && !isRedirection(e, i))
		++i;
	if (!e->magic[i].cmd)
		return (-1);
	if (ft_strstr(e->magic[i].cmd, ">&") != NULL ||
		ft_strstr(e->magic[i].cmd, "<&") != NULL)
		return (AGGREGATOR);
	else if (isRedirPipe(e, i))
		return (PIPE);
	else if (isOutputRedir(e, i))
		return (OUTPUT);
	else if (isInputRedir(e, i))
		return (INPUT);
	return (-1);
}
