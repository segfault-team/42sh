/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_options.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 14:28:45 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/07 14:28:45 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		print_history(t_env *e, char **cmd)
{
	size_t	i;
	int		arg;
	int		len_tab;

	arg = 0;
	i = -1;
	len_tab = ft_tablen(e->history);
	if (cmd[1])
	{
		arg = (size_t)atoi_bis(cmd[1]);
		if (arg == -1)
			return (ft_error("history", cmd[1], "too many arguments"));
		i = ft_tablen(e->history) - arg - 1;
	}
	if (i + 1 > (size_t)len_tab)
		i = -1;
	while (e->history[++i])
		ft_printf("%d: %s\n", i, e->history[i]);
	return (1);
}

int		clear_history_list(t_env *e)
{
	if (e->history)
	{
		ft_free_tab(e->history);
		e->history = NULL;
	}
	e->trunc_in_history = 1;
	return (1);
}

int		append_history_file_in_list(t_env *e)
{
	int		history_fd;
	int		len;
	int		nb_lines;
	char	**new;
	int		i;

	if ((history_fd = open(HIST_FILE, O_RDWR | O_CREAT, OFLAGS)) == -1)
		return (ft_error("Cannot read", HIST_FILE, NULL));
	len = ft_tablen(e->history) + 4096;
	nb_lines = 0;
	i = -1;
	if ((new = malloc(sizeof(e->history) * len)) == NULL)
		return (ft_error(NULL, "Malloc failed.", NULL));
	while (e->history[++i])
		new[i] = e->history[i];
	new[i] = NULL;
	while (++nb_lines < 4096 && get_next_line(history_fd, &new[i]) > 0)
		++i;
	new[++i] = NULL;
	ft_close(history_fd);
	e->history = new;
	return (1);
}

int		print_history_help(void)
{
	ft_printfd(2, "history: usage: history -[acdhrw]\n");
	ft_printfd(2, "-a: \t\tprint list in file\n");
	ft_printfd(2, "-c: \t\tclear the list\n");
	ft_printfd(2, "-d INDEX: \tdelete history cmd at INDEX\n");
	ft_printfd(2, "-h: \t\tshow this message\n");
	ft_printfd(2, "-r: \t\tappend history file in list\n");
	ft_printfd(2, "-w: \t\twrite list in history file\n");
	return (1);
}
