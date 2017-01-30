/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tcaps.c	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboddez <kboddez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 13:34:34 by kboddez           #+#    #+#             */
/*   Updated: 2017/01/30 15:14:55 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				dsh_putchar(int c)
{
	return (ft_putchar(c));
	/*
	char	d;

	d = c;
	return (write(1, &d, 1));
	*/
}

static int		tcaps_escape(t_env *e)
{
	if (tcaps_check_key(BUF, 27, 91, 65) || tcaps_check_key(BUF, 27, 91, 66))
		tcaps_history(e);
	else if (tcaps_check_key(BUF, 27, 91, 67) && TCAPS.nb_move < TCAPS.nb_read)
		tcaps_right(e);
	else if (tcaps_check_key(BUF, 27, 91, 68) && TCAPS.nb_move > 0)
		tcaps_left(e);
	else if (tcaps_check_key(BUF, 27, 91, 51))
		tcaps_del_fwd(e);
	return (0);
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
	else if (tcaps_check_key(BUF, 1, 0, 0))
		tcaps_rtrbeg(e);
	else if (BUF[0] == 27 && BUF[1] == 91)
		tcaps_escape(e);
	else if (tcaps_check_key(BUF, 127, 0, 0))
	{
		if (TCAPS.nb_read && TCAPS.nb_move)
			tcaps_del_bkw(e);
	}
	else if (BUF[0])
		printf("\n%d | %d | %d\n", BUF[0], BUF[1], BUF[2]);
	return (0);
}
