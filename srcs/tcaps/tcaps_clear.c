#include "shell.h"

/*
**  INSTRUCTION FOR "Ctrl + l" KEYS
**
**  cl: clear active window
**  To do : reset positions after clear && check buffer after ctrl+l
*/

void    tcaps_clear(t_env *e)
{
	xputs("cl");
	ft_putstr(e->prompt);
}
