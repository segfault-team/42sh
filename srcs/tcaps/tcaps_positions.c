/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_positions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlistrat <vlistrat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 18:43:30 by vlistrat          #+#    #+#             */
/*   Updated: 2017/04/28 18:43:30 by vlistrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	tcaps_recalc_pos(t_env *e)
{
	int		tmp;

	tmp = NB_MOVE + (int)ft_strlen(e->prompt);
	if (ioctl(0, TIOCGWINSZ, &TCAPS.ws) == -1)
	{
		TCAPS.ws.ws_col = -1;
		TCAPS.ws.ws_row = -1;
		return ;
	}
	if (TCAPS.ws.ws_col)
		TCAPS.nb_line = (tmp / (TCAPS.ws.ws_col)) + 1;
	else
		TCAPS.nb_line = tmp + 1;
	if (TCAPS.nb_line > 1 && TCAPS.ws.ws_col)
		TCAPS.nb_col = tmp % (TCAPS.ws.ws_col);
	else
		TCAPS.nb_col = tmp % (TCAPS.ws.ws_col + 1);
}
