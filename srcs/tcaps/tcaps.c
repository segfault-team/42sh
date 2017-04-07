/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 14:29:53 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/07 14:29:53 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	tcaps_bis(t_env *e)
{
	if (tcaps_check_key(BUF, 11, 0, 0) || tcaps_check_key(BUF, 16, 0, 0))
		tcaps_cut_paste(e);
	else if (tcaps_check_key(BUF, 27, 91, 51))
		tcaps_del_fwd(e);
	else if (tcaps_check_key(BUF, 27, 91, 49))
		tcaps_ctrl_arrow(e);
	else if (tcaps_check_key(BUF, 9, 0, 0) && !e->raw)
		auto_completion(e);
}

int			tcaps(t_env *e)
{
	if (BUF[0] == CTRL_D)
		tcaps_ctrl_d(e);
	else if (tcaps_is_printable(BUF) && NB_MOVE == NB_READ && !e->raw)
		tcaps_insert(e);
	else if (tcaps_check_key(BUF, 12, 0, 0))
		tcaps_clear(e);
	else if (tcaps_check_key(BUF, 27, 91, 65)
			|| tcaps_check_key(BUF, 27, 91, 66))
		tcaps_history_first_step(e);
	else if (tcaps_check_key(BUF, 27, 91, 67) && NB_MOVE < NB_READ)
		move_right(e);
	else if (tcaps_check_key(BUF, 27, 91, 68) && NB_MOVE > 0)
		tcaps_left(e);
	else if (BUF[0] == 127 && NB_READ && NB_MOVE > 0)
		tcaps_del_bkw(e);
	else if (tcaps_check_key(BUF, 5, 0, 0) || tcaps_check_key(BUF, 27, 91, 70))
		tcaps_ctrl_end(e);
	else if (tcaps_check_key(BUF, 1, 0, 0) || tcaps_check_key(BUF, 27, 91, 72))
		tcaps_ctrl_home(e);
	else
		tcaps_bis(e);
	return (0);
}
