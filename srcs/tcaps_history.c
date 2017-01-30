/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:41:22 by lfabbro           #+#    #+#             */
/*   Updated: 2017/01/30 11:41:23 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	OPEN /tmp/.history AND STORE IT IN
**	e->history TAB
*/

int		ft_read_history(t_env *e)
{
	int			fd;
	int 		i;

	i = 0;
	if ((fd = open("/tmp/.history", O_RDONLY, OPENFLAGS)) == -1)
// MANAGE ERROR
		return (ft_printf(""));
	e->history = malloc(sizeof(e->history));
	while (get_next_line(fd, &e->history[i]) > 0)
		++i;
	e->history[i] = NULL;
	if (close(fd) == -1)
		ft_printfd(2, "MANAGE ERROR");
	return (0);
}

/*
**	ADD NEW CMD TO THE END OF HTE HISTORY TAB
*/

void	ft_check_history(t_env *e)
{
	int	i;
	int	accs;

	accs = access("/tmp/.history", F_OK);
	ft_store_history(e->cmd);
	if (accs != -1)
	{
		i = ft_tablen(e->history);
		if (!ft_strcmp(e->history[i], e->line))
			e->history = ft_tabcat(e->history, e->line);
	}
	else if (e->history)
	{
		i = -1;
		while (e->history[++i])
			free(e->history[i]);
		free(e->history);
		ft_read_history(e);
	}
	else
		ft_read_history(e);
}

/*
**	MANAGE THE TERMCAPS HISTORY
**	FOR UP ARROW
*/

void	tcaps_history_up(t_env *e)
{
	if (e->history && e->history[0] && access("/tmp/.history", F_OK) != -1)
	{
		if (TCAPS.hist_move == -1)
			TCAPS.hist_move = ft_tablen(e->history) - 1;
		else if (TCAPS.hist_move)
			--TCAPS.hist_move;
		TCAPS.nb_read = ft_strlen(e->history[TCAPS.hist_move]);
		TCAPS.nb_move = TCAPS.nb_read;
		if (e->line)
			free(e->line);
		e->line = ft_strdup(e->history[TCAPS.hist_move]);
		ft_printf("%s", e->history[TCAPS.hist_move]);
	}
}

/*
**	MANAGE THE TERMCAPS HISTORY
**	FOR DOWN ARROW
*/

int		tcaps_history_down(t_env *e)
{
	int	tab_len;

	tab_len = (int)ft_tablen(e->history);
	if (e->history && e->history[0])
	{
		if (TCAPS.hist_move == -1)
			return (0);
		if (TCAPS.hist_move + 1 < tab_len)
		{
			TCAPS.nb_read = ft_strlen(e->history[TCAPS.hist_move]);
			TCAPS.nb_move = TCAPS.nb_read;
			++TCAPS.hist_move;
			ft_printf("%s", e->history[TCAPS.hist_move]);
			if (e->line)
				free(e->line);
			e->line = ft_strdup(e->history[TCAPS.hist_move]);
		}
		else if (TCAPS.hist_move + 1 == tab_len)
		{
			++TCAPS.hist_move;
			if (e->line)
				free(e->line);
			e->line = NULL;
		}
	}
	if (TCAPS.hist_move == tab_len)
		TCAPS.hist_move = -1;
	return (0);
}
