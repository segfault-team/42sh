/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_ctrl_home_end.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlistrat <vlistrat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 18:43:22 by vlistrat          #+#    #+#             */
/*   Updated: 2017/04/28 18:43:22 by vlistrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	tcaps_ctrl_d(t_env *e)
{
	if (MULTI || NB_READ)
		tcaps_del_fwd(e);
	else if (e->hdoc_nb && e->hdoc_words)
	{
		strfree(&e->line);
		if (e->hdoc_index >= 0 && e->hdoc_words[e->hdoc_index])
			e->line = ft_strdup(e->hdoc_words[e->hdoc_index]);
		else
			e->line = ft_strdup(e->hdoc_words[0]);
		tcaps_enter(e);
	}
	else
		ft_exit(e, NULL);
}

/*
**  INSTRUCTION FOR "Ctrl + a" KEYS || cmd: home
**
**  cr: return at the begining of the line
**  nd: move cursor once on the right
*/

void	tcaps_ctrl_home(t_env *e)
{
	int		i;
	int		len;

	len = NB_READ;
	while (len--)
	{
		xputs(TGETSTR_LE);
		NB_MOVE = 0;
	}
	xputs(TGETSTR_CR);
	i = ft_strlen(e->prompt);
	while (i--)
		xputs(TGETSTR_ND);
	tcaps_recalc_pos(e);
}

/*
**  INSTRUCTION FOR "Ctrl + e" KEYS || cmd: end
**
**  cr: return at the begining of the line
**  nd: move cursor once on the right
*/

void	tcaps_ctrl_end(t_env *e)
{
	tcaps_recalc_pos(e);
	while (NB_MOVE < NB_READ)
		move_right(e);
}
