#include "shell.h"

int	term_history(t_env *e)
{
	int			fd;
	int 		i;

	i = 0;
	if ((fd = open("/tmp/.history", O_RDONLY | O_CREAT, OPENFLAGS)) == -1)
		return (ft_printf("MANAGE ERROR"));
	e->history = malloc(sizeof(e->history));
	while (get_next_line(fd, &e->history[i]) > 0)
		++i;
	e->history[i] = NULL;
	if (close(fd) == -1)
		ft_printfd(2, "MANAGE ERROR");
	return (0);
}

void		check_history(t_env *e)
{
	int		i;

	i = ft_tablen(e->history) - 1;
	if (ft_strcmp(e->history[i], e->line))
		e->history = ft_tabcat(e->history, e->line);
}