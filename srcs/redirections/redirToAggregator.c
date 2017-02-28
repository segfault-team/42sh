#include "shell.h"

#define DEFAULT_VALUE 1
#define MINUS -42

static int	isolateFd(t_env *e, int red_index, int start)
{
	int	fd;

	fd = 0;
	while (isMagic(e, red_index) && isNumber(e->magic[red_index].cmd[start]))
	{
		fd = fd * 10 + (e->magic[red_index].cmd[start] - '0');
		++start;
	}
	return (fd);
}

static int	isolateFdSource(t_env *e)
{
	int	fd;

	fd = DEFAULT_VALUE;
	if (isNumber(e->magic[RED_INDEX].cmd[0]))
		fd = isolateFd(e, RED_INDEX, 0);
	else if (isOnlyNumbers(e->magic[RED_INDEX - 1].cmd))
		fd = isolateFd(e, RED_INDEX - 1, 0);
	return (fd);
}

static int isolateFdDestination(t_env *e)
{
	int	fd;
	int	start;

	fd = -1;
	start = ft_strlen(e->magic[RED_INDEX].cmd) - 1;
	if (e->magic[RED_INDEX].cmd[start] == '-' ||
		(isMagic(e, RED_INDEX + 1) && e->magic[RED_INDEX + 1].cmd[0] == '-'))
		return (MINUS);
	if (isNumber(e->magic[RED_INDEX].cmd[start]))
	{
		while(isNumber(e->magic[RED_INDEX].cmd[start - 1]))
			--start;
		fd = isolateFd(e, RED_INDEX, start);
	}
	else if (isMagic(e, RED_INDEX + 1) && isOnlyNumbers(e->magic[RED_INDEX + 1].cmd))
		fd = isolateFd(e, RED_INDEX + 1, 0);
	return (fd);
}

void		redirToAggregator(t_env *e)
{
	int	fd_src;
	int	fd_dst;

	fd_src = isolateFdSource(e);
	fd_dst = isolateFdDestination(e);
}
