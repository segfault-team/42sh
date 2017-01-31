/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_positions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlistrat <vlistrat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 09:54:24 by vlistrat          #+#    #+#             */
/*   Updated: 2017/01/31 10:37:05 by vlistrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	tcaps_recalc_pos(t_env *e)
{
	int		tmp;

	tmp = TCAPS.nb_move + ft_strlen(e->prompt);
	ioctl(0, TIOCGWINSZ, &TCAPS.ws);
	if (tmp > TCAPS.ws.ws_col)
		TCAPS.nb_line = (tmp / TCAPS.ws.ws_col) + 1;
	else
		TCAPS.nb_line = (tmp / (TCAPS.ws.ws_col - ft_strlen(e->prompt))) + 1;
	if (TCAPS.nb_line == 1)
		TCAPS.nb_col = tmp % (TCAPS.ws.ws_col - (ft_strlen(e->prompt) - 1));
	else
		TCAPS.nb_col = tmp % TCAPS.ws.ws_col;
}
