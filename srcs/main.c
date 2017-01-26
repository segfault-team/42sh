/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 17:15:54 by lfabbro           #+#    #+#             */
/*   Updated: 2017/01/26 14:31:23 by kboddez          ###   ########.fr       */
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
	if (!buf[1] && !buf[2] && (buf[0] > 32 && buf[0] < 127))
		return (1);
	return (0);
}

void	realloc_line(t_env *e, char c)
{
	char	*new;
	int		len;
	int		i;

	if (e->line)
		len = ft_strlen(e->line) + 1;
	else
		len = 1;
	new = ft_strnew(len);
	i = 0;
	if (len != 1)
		while (e->line[i++])
			new[i] = e->line[i];
	new[i] = c;
//	printf("%s | %c\n", new, c);
	if (e->line)
		free(e->line);
	e->line = new;
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
		if (check_read(e.buf))
			realloc_line(&e, e.buf[0]);
//		printf("%d | %d | %d\n", e.buf[0], e.buf[1], e.buf[2]);
		if (check_key(e.buf, 10, 0, 0))
		{
			realloc_line(&e, '\n');
//			ft_printf("boid: %s", e.line);
			ft_parse_line(&e);
//			free(e.line);
//			e.line = NULL;
			ft_putstr(e.prompt);
		}
		else
			ft_termcaps(&e);
		e.buf[0] = 0;
		e.buf[1] = 0;
		e.buf[2] = 0;
//		else if (e.line == NULL)
//			break ;
	}
	ft_putendl("exit");
	ft_env_free(&e);
	return (e.exit);
}
