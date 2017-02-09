/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_banner.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:26:14 by lfabbro           #+#    #+#             */
/*   Updated: 2017/02/09 16:12:49 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void		ft_banner(void)
{
	ft_printf("\n                      .,,uod8B8bou,,.\n");
	ft_printf("             ..,uod8BBBBBBBBBBBBBBBBRPFT?l!i:.\n");
	ft_printf("         ,=m8BBBBBBBBBBBBBBBRPFT?!||||||||||||||\n");
	ft_printf("         !...:!TVBBBRPFT||||||||||!!^^\"\"'%s...%s||||\n", BLUE, WHITE);
	ft_printf("         !.......:!?|||||!!^^\"\"'%s............%s||||\n", BLUE, WHITE);
	ft_printf("         !.........||||%s.....................%s||||\n", BLUE, WHITE);
	ft_printf("         !.........||||%s....%s%s%s", BLUE, GREEN, "## > ", ITALIC);
	ft_printf("%s%s........%s||||\n", "21sh", BLUE, WHITE);
	ft_printf("         !.........||||%s.....................%s||||\n", BLUE, WHITE);
	ft_printf("         !.........||||%s.....................%s||||\n", BLUE, WHITE);
	ft_printf("         !.........||||%s.....................%s||||\n", BLUE, WHITE);
	ft_printf("         !.........||||%s.....................%s||||\n", BLUE, WHITE);
	ft_printf("         `.........||||%s....................%s,||||\n", BLUE, WHITE);
	ft_printf("          .;.......||||%s.............%s_.-!!|||||\n", BLUE, WHITE);
	ft_printf("   .,uodWBBBBb.....||||%s.......%s_.-!!|||||||||!:'\n", BLUE, WHITE);
	ft_printf("!YBBBBBBBBBBBBBBb..!|||:..-!!|||||||!iof68BBBBBb....\n");
	ft_printf("!..YBBBBBBBBBBBBBBb!!||||||||!iof68BBBBBBRPFT?!::   `.\n");
	ft_printf("!....YBBBBBBBBBBBBBBbaaitf68BBBBBBRPFT?!:::::::::     `.\n");
	ft_printf("!......YBBBBBBBBBBBBBBBBBBBRPFT?!::::::;:!^\"`;:::       `.\n");
	ft_printf("!........YBBBBBBBBBBRPFT?!::::::::::^''...::::::;         iBBbo.\n");
	banner_ii();
}
