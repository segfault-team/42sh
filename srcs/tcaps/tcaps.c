/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tcaps.c	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboddez <kboddez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 13:34:34 by kboddez           #+#    #+#             */
/*   Updated: 2017/02/13 18:20:32 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				dsh_putchar(int c)
{
	return (ft_putchar(c));
}

int 			tcaps(t_env *e)
{
	if (!tcaps_check_key(BUF, 27, 91, 65) && !tcaps_check_key(BUF, 27, 91, 66))
		TCAPS.hist_move = -1;
	if (BUF[0] == 4)
		ft_exit(e);
	else if (tcaps_check_read(BUF))
		tcaps_insert(e);
	else if (tcaps_check_key(BUF, 12, 0, 0))
		tcaps_clear(e);
	else if (tcaps_check_key(BUF, 27, 91, 65) || tcaps_check_key(BUF, 27, 91, 66))
		tcaps_history(e);
	else if (tcaps_check_key(BUF, 27, 91, 67) && TCAPS.nb_move < TCAPS.nb_read)
		tcaps_right(e);
	else if (tcaps_check_key(BUF, 27, 91, 68) && TCAPS.nb_move > 0)
		tcaps_left(e);
	else if (BUF[0] == 127 && TCAPS.nb_read && TCAPS.nb_move > 0)
		tcaps_del_bkw(e);
	else if (tcaps_check_key(BUF, 27, 91, 49))
		tcaps_ctrl_mov(e);
	else if (tcaps_check_key(BUF, 5, 0, 0) || tcaps_check_key(BUF, 27, 91, 70))
		tcaps_ctrl_end(e);
	else if (tcaps_check_key(BUF, 1, 0, 0) || tcaps_check_key(BUF, 27, 91, 72))
		tcaps_ctrl_home(e);
	else if (tcaps_check_key(BUF, 11, 0, 0) || tcaps_check_key(BUF, 16, 0, 0))
		tcaps_cut_paste(e);
	else if (tcaps_check_key(BUF, 27, 91, 51))
		tcaps_del_fwd(e);
	else if (is_paste(BUF))
		ft_paste(e, BUF);
	//	else if (BUF[0])
	//		printf("\n%d | %d | %d\n", BUF[0], BUF[1], BUF[2]);
	return (0);
}
