/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:41:22 by lfabbro           #+#    #+#             */
/*   Updated: 2017/02/08 17:06:13 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
 **	OPEN /tmp/.history AND STORE IT IN
 **	e->history TAB
 */

size_t	ft_history_len(void)
{
	char	*line;
	size_t	len;
	int		fd;

	len = 0;
	if ((fd = open("/tmp/.history", O_RDONLY, OPENFLAGS)) < 0)
		return (ft_error("open", "could not open", "/tmp/.history"));
	while (get_next_line(fd, &line) > 0 && ++len)
		free(line);
	if (close(fd) < 0)
		return (ft_error("close", "could not close file", "/tmp/.history"));
	return (len);
}

int		ft_read_history(t_env *e)
{
	int			fd;
	int 		i;
	size_t		len;
	char		*line;

	i = -1;
	len = 0;
	line = NULL;
	if ((len = ft_history_len()))
	{
		// MANAGE ERRORS
		if ((fd = open("/tmp/.history", O_RDONLY, OPENFLAGS)) < 0)
			return (ft_error("open", "could not open", "/tmp/.history"));
		if ((e->history = ft_tabnew(len)) == NULL)
			return (ft_error("malloc", "failed", NULL));
		while (get_next_line(fd, &line) > 0)
		{
			e->history[++i] = ft_strdup(line);
			free(line);
		}
		if (close(fd) < 0)
			return (ft_error("close", "could not close file", "/tmp/.history"));
		return (0);
	}
	return (-1);
}

/*
 **	ADD NEW CMD TO THE END OF HTE HISTORY TAB
 */

void	ft_check_history(t_env *e)
{
	int		i;
	int		accs;
	char	**tmp;

	accs = access("/tmp/.history", F_OK);
	if (e->cmd)
		ft_store_history(e->cmd);
	tmp = NULL;
	if (accs != -1)
	{
		i = ft_tablen(e->history);
		if (!ft_strcmp(e->history[i], e->line))
		{
			tmp = e->history;
			e->history = ft_tabcat(e->history, e->line);
			if (tmp)
				ft_free_tab(tmp);
		}
	}
	else if (e->history)
	{
		ft_free_tab(e->history);
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
