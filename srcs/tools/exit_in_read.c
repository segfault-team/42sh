#include "shell.h"

void	exit_in_read(t_env *e)
{
	ft_prompt(e->prompt);
	ft_reset_line(e);
}
