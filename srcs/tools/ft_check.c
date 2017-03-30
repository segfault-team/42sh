#include "shell.h"

int		check_last_char(t_env *e, char c)
{
	return (e->line[NB_READ - 1] == c && e->line[NB_READ - 2] != '\\');
}

int		check_prev_last_char(t_env *e, char c)
{
	return (e->line[NB_READ - 2] == c && e->line[NB_READ - 3] != '\\');
}
