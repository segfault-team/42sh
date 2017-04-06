#include "shell.h"

#define DEFAULT_VALUE_INPUT 0
#define DEFAULT_VALUE_OUTPUT 1
#define MINUS -42
#define ERROR -420
#define DEV_DEVICE -666
#define ERROR_FILENUMBER -4242

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

static int	isolate_file(t_env *e, int i)
{
	int		j;
	int		k;
	char	*file;
	int		ret;

	j = 1;
	k = -1;
	if (space_after_aggre(e->magic[i].cmd))
		return (open(e->magic[i + 1].cmd, O_CREAT | O_TRUNC, OFLAGS));
	while (j && (e->magic[i].cmd[j] != '&' || e->magic[i].cmd[j - 1] != '>'))
		++j;
	file = ft_strnew((int)ft_strlen(e->magic[i].cmd) - j);
	while (e->magic[i].cmd[++j])
		file[++k] = e->magic[i].cmd[j];
	ret = open_file(file, ONE_RED_FLAGS, OFLAGS);
	strfree(&file);
	return (ret);
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

int			isolate_fd_destination(t_env *e, int *is_file)
{
	int		fd;
	int		start;

	*is_file = 0;
	fd = ERROR;
	start = ft_strlen(e->magic[RED_INDEX].cmd) - 1;
	if (e->magic[RED_INDEX].cmd[start] == '-' ||
		(is_magic(e, RED_INDEX + 1) && e->magic[RED_INDEX + 1].cmd[0] == '-'))
		return (MINUS);
	if (is_number(e->magic[RED_INDEX].cmd[start]))
	{
		while (is_number(e->magic[RED_INDEX].cmd[start - 1]))
			--start;
		return (isolate_fd(e, RED_INDEX, start));
	}
	else if (is_magic(e, RED_INDEX + 1) &&
			is_only_numbers(e->magic[RED_INDEX + 1].cmd))
		return (isolate_fd(e, RED_INDEX + 1, 0));
	else
	{
		*is_file = 1;
		return (isolate_file(e, RED_INDEX));
	}
	return (fd);
}
