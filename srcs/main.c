/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 17:15:54 by lfabbro           #+#    #+#             */
/*   Updated: 2017/01/28 14:58:18 by kboddez          ###   ########.fr       */
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

int check_key(char buf[3], int a, int b, int c)
{
	if (buf[0] == (char)a && buf[1] == (char)b && buf[2] == (char)c)
		return (1);
	return (0);
}

int	check_read(char buf[3])
{
	if (!buf[1] && !buf[2] && (buf[0] >= 32 && buf[0] < 126))
		return (1);
	return (0);
}

int				main(int ac, char **av, char **env)
{
	t_env	e;

	ft_banner();
	ft_init(&e, ac, av, env);
	ft_set_sig_handler();
	ft_putstr(e.prompt);
	while (e.x)
	{
		read(0, e.buf, 3);
		if (!e.tcaps.check_move)
			e.tcaps.nb_move = e.tcaps.nb_read;
		if (check_read(e.buf))
		{
			if (e.tcaps.nb_move == e.tcaps.nb_read)
				e.line = realloc_line(&e, e.buf[0]);
			else
				e.line = realloc_insert_char(&e, e.buf[0]);
			e.tcaps.nb_read = ft_strlen(e.line);
		}
		else if (e.buf[0] == 127)
			e.line = realloc_delete_char(&e);
//		ft_printf("%d | %d | %d\n", e.tcaps.nb_move, e.tcaps.nb_read, e.tcaps.check_move);
		if (check_key(e.buf, 10, 0, 0))
		{
			ft_putchar('\n');
			if (ft_parse_line(&e))
				ft_putchar('\n');
			check_history(&e);
			e.tcaps.nb_move = 0;
			e.tcaps.nb_read = 0;
			if (!ft_strstr(e.line, "exit"))
				ft_putstr(e.prompt);
			free(e.line);
			e.line = NULL;
		}
		else
			ft_termcaps(&e);
		e.buf[0] = 0;
		e.buf[1] = 0;
		e.buf[2] = 0;
		if (e.tcaps.nb_move < e.tcaps.nb_read)
			e.tcaps.check_move = 1;
	}
	ft_env_free(&e);
	return (e.exit);
}
