/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_positions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlistrat <vlistrat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 09:54:24 by vlistrat          #+#    #+#             */
/*   Updated: 2017/01/31 14:32:45 by vlistrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	tcaps_recalc_pos(t_env *e)
{
	int		tmp;

	tmp = TCAPS.nb_move + ft_strlen(e->prompt);
	ioctl(0, TIOCGWINSZ, &TCAPS.ws);
	TCAPS.nb_line = (tmp / (TCAPS.ws.ws_col)) + 1;
	if (TCAPS.nb_line)
		TCAPS.nb_col = tmp % (TCAPS.ws.ws_col);
	else
		TCAPS.nb_col = (tmp % (TCAPS.ws.ws_col + 1)) + ft_strlen(e->prompt) - 1;
}
