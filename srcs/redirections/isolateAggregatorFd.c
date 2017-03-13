#include "shell.h"

#define DEFAULT_VALUE_INPUT 0
#define DEFAULT_VALUE_OUTPUT 1
#define MINUS -42
#define ERROR -420

static int  isolateFd(t_env *e, int red_index, int start)
{
	int fd;

	fd = 0;
	while (isMagic(e, red_index) &&
		   isNumber(e->magic[red_index].cmd[start]))
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

int  isolateFdSource(t_env *e)
{
	int fd;

	if (ft_strstr(e->magic[RED_INDEX].cmd, ">&"))
		fd = DEFAULT_VALUE_OUTPUT;
	else
		fd = DEFAULT_VALUE_INPUT;
	if (isNumber(e->magic[RED_INDEX].cmd[0]))
		fd = isolateFd(e, RED_INDEX, 0);
	else if (!isNumber(e->magic[RED_INDEX].cmd[0]) &&
			 e->magic[RED_INDEX].cmd[0] != '>' &&
			 e->magic[RED_INDEX].cmd[0] != '<')
		fd = ERROR;
	else if (isOnlyNumbers(e->magic[RED_INDEX - 1].cmd))
		fd = isolateFd(e, RED_INDEX - 1, 0);
	return (fd);
}

int isolateFdDestination(t_env *e)
{
	int fd;
	int start;

	fd = ERROR;
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
