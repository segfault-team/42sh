/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 17:15:54 by lfabbro           #+#    #+#             */
/*   Updated: 2016/12/15 19:27:34 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		ft_banner(void)
{
	ft_putstr("       ___         ___         ___         ___         _");
	ft_putendl("__     ");
	ft_putstr("      /__/\\       /  /\\       /  /\\       /  /\\     ");
	ft_putendl("  /__/\\    ");
	ft_putstr("     |  |::\\     /  /::\\     /  /::\\     /  /:/_     ");
	ft_putendl(" \\  \\:\\   ");
	ft_putstr("     |  |:|:\\   /  /:/\\:\\   /  /:/\\:\\   /  /:/ /\\ ");
	ft_putendl("     \\__\\:\\  ");
	ft_putstr("   __|__|:|\\:\\ /  /:/~/::\\ /  /:/~/:/  /  /:/ /::\\ _");
	ft_putendl("__ /  /::\\ ");
	ft_putstr("  /__/::::| \\:/__/:/ /:/\\:/__/:/ /:/__/__/:/ /:/\\:/__");
	ft_putendl("/\\  /:/\\:\\ ");
	ft_putstr("  \\  \\:\\~~\\__\\\\  \\:\\/:/__\\\\  \\:\\/:::::\\  \\");
	ft_putendl(":\\/:/~/:\\  \\:\\/:/__\\/");
	ft_putstr("   \\  \\:\\      \\  \\::/     \\  \\::/~~~~ \\  \\::/ ");
	ft_putendl("/:/ \\  \\::/     ");
	ft_putstr("    \\  \\:\\      \\  \\:\\      \\  \\:\\      \\__\\/");
	ft_putendl(" /:/   \\  \\:\\     ");
	ft_putstr("     \\  \\:\\      \\  \\:\\      \\  \\:\\       /__/:");
	ft_putendl("/     \\  \\:\\    ");
	ft_putstr("      \\__\\/       \\__\\/       \\__\\/       \\__\\/ ");
	ft_putendl("      \\__\\/   ");
}

int				main(int ac, char **av, char **env)
{
	t_env	e;

	ft_banner();
	ft_init(&e, ac, av, env);
	ft_set_sig_handler();
	while (e.x)
	{
		ft_putstr(e.prompt);
		if (get_next_line(0, &e.line) > 0)
		{
			ft_parse_line(&e);
		}
		else if (e.line == NULL)
			break ;
		free(e.line);
		e.line = NULL;
	}
	ft_putendl("exit");
	ft_env_free(&e);
	return (e.exit);
}
