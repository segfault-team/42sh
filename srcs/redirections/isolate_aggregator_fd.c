#include "shell.h"

#define DEFAULT_VALUE_INPUT 0
#define DEFAULT_VALUE_OUTPUT 1
#define MINUS -42
#define ERROR -420
#define DEV_DEVICE -666

static int	isolate_fd(t_env *e, int red_index, int start)
{
	int		fd;

	fd = 0;
	while (is_magic(e, red_index) &&
			is_number(e->magic[red_index].cmd[start]))
	{
		fd = fd * 10 + (e->magic[red_index].cmd[start] - '0');
		++start;
	}
	if (e->magic[red_index].cmd[start] &&
		e->magic[red_index].cmd[start] != '>' &&
		e->magic[red_index].cmd[start] != '<')
		return (ERROR);
	return (fd);
}

int			isolate_fd_source(t_env *e)
{
	int		fd;

	if (ft_strstr(e->magic[RED_INDEX].cmd, ">&"))
		fd = DEFAULT_VALUE_OUTPUT;
	else
		fd = DEFAULT_VALUE_INPUT;
	if (is_number(e->magic[RED_INDEX].cmd[0]))
		fd = isolate_fd(e, RED_INDEX, 0);
	else if (!is_number(e->magic[RED_INDEX].cmd[0]) &&
			e->magic[RED_INDEX].cmd[0] != '>' &&
			e->magic[RED_INDEX].cmd[0] != '<')
		fd = ERROR;
	else if (is_only_numbers(e->magic[RED_INDEX - 1].cmd))
		fd = isolate_fd(e, RED_INDEX - 1, 0);
	return (fd);
}

int			isolate_fd_destination(t_env *e)
{
	int		fd;
	int		start;

	fd = ERROR;
	start = ft_strlen(e->magic[RED_INDEX].cmd) - 1;
	if (e->magic[RED_INDEX].cmd[start] == '-' ||
		(is_magic(e, RED_INDEX + 1) && e->magic[RED_INDEX + 1].cmd[0] == '-'))
		return (MINUS);
	if (is_number(e->magic[RED_INDEX].cmd[start]))
	{
		while (is_number(e->magic[RED_INDEX].cmd[start - 1]))
			--start;
		fd = isolate_fd(e, RED_INDEX, start);
	}
	else if (is_magic(e, RED_INDEX + 1) &&
			is_only_numbers(e->magic[RED_INDEX + 1].cmd))
		fd = isolate_fd(e, RED_INDEX + 1, 0);
	return (fd);
}
