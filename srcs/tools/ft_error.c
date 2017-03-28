#include "shell.h"

int		ft_error(char *util, char *msg, char *what)
{
	if (what)
		ft_printfd(2, "%s: %s %s", util, msg, what);
	else if (util)
		ft_printfd(2, "%s: %s", util, msg);
	else
		ft_printfd(2, "%s", msg);
	return (-1);
}
