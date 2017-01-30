#include "shell.h"

static void	banner_ii(void)
{
	ft_printf("`..........YBRPFT?!::::::::::::::::::::::::;iof68bo.      WBBBBbo.\n");
	ft_printf("  `..........:::::::::::::::::::::::;iof688888888888b.     `YBBBP^'\n");
	ft_printf("    `........::::::::::::::::;iof688888888888888888888b.     `\n");
	ft_printf("     `......:::::::::;iof688888888888888888888888888888b.\n");
	ft_printf("       `....:::;iof688888888888888888888888888888888899fT!\n");
	ft_printf("         `..::!8888888888888888888888888888888899fT|!^\"'\n");
	ft_printf("           `' !!988888888888888888888888899fT|!^\"'\n");
	ft_printf("             `!!8888888888888888899fT|!^\"'\n");
	ft_printf("               `!988888888899fT|!^\"'\n");
	ft_printf("                 `!9899fT|!^\"'\n");
	ft_printf("                   `!^\"'\n\n");
}

void		banner(t_env *e)
{
	ft_printf("\n                      .,,uod8B8bou,,.\n");
	ft_printf("             ..,uod8BBBBBBBBBBBBBBBBRPFT?l!i:.\n");
	ft_printf("         ,=m8BBBBBBBBBBBBBBBRPFT?!||||||||||||||\n");
	ft_printf("         !...:!TVBBBRPFT||||||||||!!^^\"\"'   ||||\n");
	ft_printf("         !.......:!?|||||!!^^\"\"'            ||||\n");
	ft_printf("         !.........||||                     ||||\n");
	ft_printf("         !.........||||     %s%s%s", GREEN, "## > ", ITALIC);
	ft_printf("%s%s%s       ||||\n", BLUE, "boid", "\x1b[0m", WHITE);
	ft_printf("         !.........||||                     ||||\n");
	ft_printf("         !.........||||                     ||||\n");
	ft_printf("         !.........||||                     ||||\n");
	ft_printf("         !.........||||                     ||||\n");
	ft_printf("         `.........||||                    ,||||\n");
	ft_printf("          .;.......||||               _.-!!|||||\n");
	ft_printf("   .,uodWBBBBb.....||||       _.-!!|||||||||!:'\n");
	ft_printf("!YBBBBBBBBBBBBBBb..!|||:..-!!|||||||!iof68BBBBBb....\n");
	ft_printf("!..YBBBBBBBBBBBBBBb!!||||||||!iof68BBBBBBRPFT?!::   `.\n");
	ft_printf("!....YBBBBBBBBBBBBBBbaaitf68BBBBBBRPFT?!:::::::::     `.\n");
	ft_printf("!......YBBBBBBBBBBBBBBBBBBBRPFT?!::::::;:!^\"`;:::       `.\n");
	ft_printf("!........YBBBBBBBBBBRPFT?!::::::::::^''...::::::;         iBBbo.\n");
	banner_ii();
	ft_putstr(e->prompt);
}
