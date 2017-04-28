#include "shell.h"

/*
**  INSTRUCTION FOR "Ctrl + l" KEYS
**
**  cl: clear active window
**  To do : reset positions after clear && check buffer after ctrl+l
*/

void	tcaps_clear(t_env *e)
{
	xputs(TGETSTR_CL);
	ft_prompt(e->prompt);
	ft_printf("%s", e->line ? e->line : "");
}
