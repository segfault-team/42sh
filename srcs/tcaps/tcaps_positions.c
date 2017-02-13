/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_positions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlistrat <vlistrat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 09:54:24 by vlistrat          #+#    #+#             */
/*   Updated: 2017/02/13 18:20:12 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	tcaps_recalc_pos(t_env *e)
{
	int		tmp;

	tmp = TCAPS.nb_move + (int)ft_strlen(e->prompt);
	ioctl(0, TIOCGWINSZ, &TCAPS.ws);
	if (TCAPS.ws.ws_col)
		TCAPS.nb_line = (tmp / (TCAPS.ws.ws_col)) + 1;
	else
		TCAPS.nb_line = tmp + 1;
	if (TCAPS.nb_line && TCAPS.ws.ws_col)
		TCAPS.nb_col = tmp % (TCAPS.ws.ws_col);
	else
		TCAPS.nb_col = (tmp % (TCAPS.ws.ws_col + 1)) + ft_strlen(e->prompt) - 1;
}
